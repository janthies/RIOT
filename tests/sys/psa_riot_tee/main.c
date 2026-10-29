/*
 * SPDX-FileCopyrightText: 2024 HAW Hamburg
 * SPDX-License-Identifier: LGPL-2.1-only
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Tests for the PSA Crypto API with the riot-tee (TrustZone-M) backend
 *
 * @author      Lena Boeckmann <lena.boeckmann@haw-hamburg.de>
 *
 * @}
 */

#include "periph_cpu.h"
#include "test_utils.h"

int main(void)
{
    /* Boot-time evaluation: the phase pin of BL1 (P0.10), which riot-tee
       keeps toggling, toggles once more when RIOT reaches main(). */
    NRF_P0->OUT ^= 1 << 10;
    TESTS_START();
    psa_crypto_init();
    TESTS_RUN(tests_psa_import_and_seal_key());
    TESTS_RUN(tests_psa_generate_sealed_key());
    TESTS_RUN(tests_psa_aes_128_encrypt_decrypt());
    TESTS_RUN(tests_psa_hash_sha256_gen());
    TESTS_END();
    return 0;
}
