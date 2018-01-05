// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x3c;
        pchMessageStart[1] = 0x2e;
        pchMessageStart[2] = 0x2e;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("04478569856c6ebbf49144578961207275d71cb009f201c118b00cf8e77641c7f1e63e330ba909842c009af375c0f5c1c7368e8d7e2066168c40ce3cb629cf212f");
        nDefaultPort = 32229;
        nRPCPort = 32230;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "Masternode update v2 ";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = nGenesisBlockReward;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1515164554, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1515164554; // Mon, 01 May 2017 00:00:00 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 533575;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == e7dba9a3b6015db6a7e3184106c0f813f525b9d4528f36d6f4da0927c9bf0a5f
        block.nTime = 1493596800
        block.nNonce = 192744
        block.GetHash = 00001f66cb3ba8f5776cb750d621cb3390200580cc39f076b3f61efcf191fba0
        */


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == nGenesisBlock);
        assert(genesis.hashMerkleRoot == nGenesisMerkle);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,102);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,57);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,55);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,59);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("138.197.44.71",  "138.197.44.71"));
        vSeeds.push_back(CDNSSeedData("138.197.44.71",  "138.197.44.71"));
        vSeeds.push_back(CDNSSeedData("138.197.44.71",  "138.197.44.71"));
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "iGrwXgFQbhiSBsxVSSCeQmty2qzCt4uS7Q";
        nEndPoWBlock = 1500;
        nStartPoSBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0xcc;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0458uxab003c828cdd9cf4db2ebbde8e1cecb3bbfa8b3127fcb9dd9b84d44112080827ed7c49a648af9fe788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 32230;
        nRPCPort = 10562;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1515164554;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 20015;


        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == e7dba9a3b6015db6a7e3184106c0f813f525b9d4528f36d6f4da0927c9bf0a5f
        block.nTime = 1493596830
        block.nNonce = 5925
        block.GetHash = 0000ae1d0aaeda3c5554fc4d5192c481d002174e33985bb8c855edd899fd0346
        */



        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == hashTestNetGenesisBlock);

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,103);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,39);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,63);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,37);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        return false;
    }

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    }  else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
