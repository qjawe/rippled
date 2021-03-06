//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2016 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_CONDITIONS_ED25519_H
#define RIPPLE_CONDITIONS_ED25519_H

#include <ripple/conditions/Condition.h>
#include <ripple/conditions/Fulfillment.h>
#include <ripple/protocol/PublicKey.h>
#include <ripple/protocol/SecretKey.h>
#include <array>
#include <cstdint>

namespace ripple {
namespace cryptoconditions {

class Ed25519 final
    : public Fulfillment
{
    static std::size_t constexpr signature_size_ = 64;
    static std::size_t constexpr pubkey_size_ = 32;

    std::array<std::uint8_t,
        pubkey_size_ + signature_size_> payload_;

public:
    Ed25519 () = default;

    /** Create a fulfillment given a keypair and the message */
    Ed25519 (
        SecretKey const& secretKey,
        PublicKey const& publicKey,
        Slice message);

    /** Create a fulfillment given a secret key and the message */
    Ed25519 (
        SecretKey const& secretKey,
        Slice message);

    Condition
    condition() const override;

    std::uint16_t
    type () const override
    {
        return condition_ed25519;
    }

    std::uint32_t
    features () const override
    {
        return feature_ed25519;
    }

    bool
    ok () const override
    {
        return true;
    }

    std::size_t
    payloadSize () const override
    {
        return payload_.size();
    }

    Buffer
    payload() const override
    {
        return { payload_.data(), payload_.size() };
    }

    bool
    validate (Slice data) const override;

    bool
    parsePayload (Slice s) override;
};

}

}

#endif
