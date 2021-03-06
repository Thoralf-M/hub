/*
 * Copyright (c) 2019 IOTA Stiftung
 * https://github.com/iotaledger/hub
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef HUB_BUNDLE_CREATE_BUNDLE_H_
#define HUB_BUNDLE_CREATE_BUNDLE_H_

#include <gflags/gflags.h>
#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "common/crypto/types.h"
#include "hub/db/types.h"

DECLARE_uint32(numBundlesToMine);

namespace hub {
namespace bundle_utils {

/// Compute and serialize a bundle made up of all the deposits and withdrawals
/// identified during the sweep.
/// @param[in] deposits - a list of deposit transactions
/// @param[in] hubInputs - a list of internal transfers
/// @param[in] withdrawals - a list of withdrawal transactions
/// @param[in] hubOutput - a list of db::TransferOutput structures
/// @param[in] alreadySignedBundleHashes - if not empty, this means we should
/// force signature and mine for a bundle an already spent address
/// @return a std::tuple containing
/// - the bundle hash
/// - the serialized bundle
std::tuple<common::crypto::Hash, std::string> createBundle(
    const std::vector<db::TransferInput>& deposits,
    const std::vector<db::TransferInput>& hubInputs,
    const std::vector<db::TransferOutput>& withdrawals,
    const nonstd::optional<db::TransferOutput> hubOutputOptional,
    const std::vector<std::string>& alreadySignedBundleHashes = {});

/// Persist the bundle data to database
/// identified during the sweep.
/// @param[in] bundle - the bundle hash and its serialized value
/// @param[in] deposits - a list of deposit transactions
/// @param[in] hubInputs - a list of internal transfers
/// @param[in] withdrawals - a list of withdrawal transactions
/// @param[in] hubOutput - the hub address into which the remainder is
/// deposited
void persistToDatabase(std::tuple<common::crypto::Hash, std::string> bundle,
                       const std::vector<db::TransferInput>& deposits,
                       const std::vector<db::TransferInput>& hubInputs,
                       const std::vector<db::TransferOutput>& withdrawals,
                       const nonstd::optional<db::TransferOutput> hubOutput);

/// Creates a new hub address to which funds that remain after a transfer
/// can be moved.
/// @param[in] remainder
/// @return a db::TransferOutput structure containing
/// - the new hub address
/// - the id of the new hub address
/// - the remainder
hub::db::TransferOutput getHubOutput(uint64_t remainder);

}  // namespace bundle_utils
}  // namespace hub

#endif  // HUB_BUNDLE_CREATE_BUNDLE_H_
