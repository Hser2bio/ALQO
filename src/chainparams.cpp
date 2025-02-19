// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "streams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>


struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (   0, uint256S("000040f1123764b16ac29f9c6c994e5beeacaf21f751062f5ab2c651351e0db1"))
    ( 100, uint256S("00000009276dd4b319f655cba99fb27cccc3fbff6f39b9ee13b4c96b13148b24"))
    ( 250, uint256S("000000011cc961ad1a8b5f08f7b9dbc0039e610544d4792b9fe7e3312b0ec6a4"))
    ( 500, uint256S("bea487fb24d423a14ed5e928e1a7579c258ced83fc9edffa8509109f62b30719"))
	(1000, uint256S("8c385cf5dc4a1792c6b5c445360eac67c948a7e52d3c8ab911fcef7b210112c5"))
	(1500, uint256S("288adf835a70d4d521328e7363005301486e0b18106161b6d3def940a71a9c42"))
	(2500, uint256S("35728ae422dd4d6418b3536fca7887c2fdea5de23fe097076ab0c61185e77764"))
	(5500, uint256S("93bc7a990f6b09ea49adf325eb1c5839c3632140e08c896b5826fe9a84e5190b"))
	(7500, uint256S("0ea244cf2898d729f88a03495649012da266e5717d062c585baa49e64745af3e"))
	(10500, uint256S("614b39de5bc267e9b7b08025ce7dee7115df1e1a3e74ee32ab1f0da048915fa0"))
	(15500, uint256S("fee1b74be04172d3a40d127b86ba69e670f9e62f6c843b1db521273974faea3f"))
	(25500, uint256S("5cfc7f1a740a7a461268576fb1db6084f9d3839ac787428923fa0cb4b64b3f8c"))
	(45500, uint256S("b87583aa0f9ab53721131692f0d13b5c6dccfa5384600c80422b7ce7fec9bbc0"))
	(75500, uint256S("97a0a8916b4bd9d4cec62227ac915bb2076a3c2127f4f045e89538f732077321"))
	(95500, uint256S("399fe2c720d76e18dcb376e004cc7c314ad844b4e0f9bc1a56c55e205f521c11"))
	(135500, uint256S("b941063d23af20033b5af03d61a422d907ba536371a9c3888d4efc76c3bb4699"))
	(175500, uint256S("e0912ed223e88b6f30a4adbab69b6e90e401f55d84a24f3179a971051630a364"))
	(225500, uint256S("53c8884259210e57f47a1b2d0906b0a91f1bba54c2ab9a0b150d3d3319dc2732"))
	(350000, uint256S("426700322ed640ac20683ddeb10c259b05c3a30c4d763e8dc4c8758620a41905"))
	(400500, uint256S("816d72abe5bcca4c00dd9461c69c34d1364fc988bc51d81c0a808b779f3d5cb7"))
	(650500, uint256S("edd5e61c38bbfcdba3d456ccd2082e0bdb19cc900dd90e31c2e438858846ef75"))
	(750500, uint256S("24ce7e69e12cc68e2f2b3b3803006711b3a74fc27c3ef34d50344a3707ff3971"))
	(950500, uint256S("d9128ff3dbcf47429c823238e698ebc4b69011bc8423a82c230024daded31207"))
	(1000500, uint256S("e1925cbbd761efc55065850083a51bcd853bd4b062154b1a117688617f918e06"))
	(1125507, uint256S("077e281b61ca5a23ed24a418973c200a13b546ff9abbbf73d067849c73b9b06d"))
	(1135521, uint256S("09b2b6d1a95b4cebf66af998e795bdf10be6386f41ee0f80217f5dc5997fe1a0"))
	;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1644826249, // * UNIX timestamp of last checkpoint block
    2420824,        // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    576         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (   0, uint256("0000000000000000000000000000000000000000000000000000000000000000"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet, 0, 0, 0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (   0, uint256("0000000000000000000000000000000000000000000000000000000000000000"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest, 0, 0, 0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0xae;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("034696359afb387e2aa97bd344546a10a7a2f8982f8e00658a17240152f8bf6fea");
        nDefaultPort = 20480;
        bnProofOfWorkLimit =  uint256S("0000fffff0000000000000000000000000000000000000000000000000000000");
        bnProofOfStakeLimit = uint256S("0001ffff00000000000000000000000000000000000000000000000000000000");
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        nMinerThreads = 0;
        nTargetSpacing = 60;
        nMaturity = 30;
        nStakeMinAge = 60 * 60;
        nStakeMaxAge = 30 * 24 * 60 * 60;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;
        nMasternodeCollateral = 10000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 300;
        nHeaderCastBug = 20000;
        nModifierUpdateBlock = 33554432;
        nInvalidAmountFiltered = 0;

        nSupplyBeforeFakeSerial = 0;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "ALQO launch 06122019";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1575570915;
        genesis.nBits = 0x1f00ffff;
        genesis.nNonce = 13513;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256S("000040f1123764b16ac29f9c6c994e5beeacaf21f751062f5ab2c651351e0db1"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 211);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkPubKey = "038c7d772ea3ff04122dd249284ebcdbfcb773e140ab914a39932143a41f55e872";
        strObfuscationPoolDummyAddress = "aixE2v6zn2e2pznDKoAPvii17MmbkdLjHS";
        nStartMasternodePayments = genesis.nTime;

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x90;
        pchMessageStart[2] = 0x47;
        pchMessageStart[3] = 0x90;
        vAlertPubKey = ParseHex("034696359afb387e2aa97bd344546a10a7a2f8982f8e00658a17240152f8bf6fea");
        nDefaultPort = 20480;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        nMinerThreads = 0;
        nTargetSpacing = 60;
        nMaturity = 100;
        nStakeMinAge = 60 * 60;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;
        nMasternodeCollateral = 10000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 250;
        nModifierUpdateBlock = 50;
        nInvalidAmountFiltered = 0;
        nBlockStakeModifierlV2 = 1967000;
        nSupplyBeforeFakeSerial = 0;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = true;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "U.S. News & World Report Jan 28 2016 With His Absence, Trump Dominates Another Debate";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2402015;

        CDataStream stream(ParseHex("010000000000000000000000000000000000000000000000000000000000000000000000cbac770aa589bb71f32b958070dbee3c97d71572a96a825bc60e1e0faf6b955568a6d95df0ff0f1e67f010000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1704ffff001d01040f414c514f202d203234313132303139ffffffff01000000000000000043410457c56ed69a1f42398804504fcab82f430cc864c8fc8cd25b76e141d12c13012ee9d500e11f84d5f75f5c669e88ca196142ddb7406d3635d840fa5e9d2a6bb100ac00000000"), SER_NETWORK, PROTOCOL_VERSION);
        stream >> genesis;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256S("000000b8486c11f11b0970584997554e317521b37a4673bcd551bebee593d294"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 211);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strObfuscationPoolDummyAddress = "aixE2v6zn2e2pznDKoAPvii17MmbkdLjHS";
        nStartMasternodePayments = genesis.nTime + 5400;

        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x47;
        pchMessageStart[1] = 0x90;
        pchMessageStart[2] = 0x47;
        pchMessageStart[3] = 0x90;
        vAlertPubKey = ParseHex("034696359afb387e2aa97bd344546a10a7a2f8982f8e00658a17240152f8bf6fea");
        nDefaultPort = 20480;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        nMinerThreads = 0;
        nTargetSpacing = 60;
        nMaturity = 100;
        nStakeMinAge = 60 * 60;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;
        nMasternodeCollateral = 10000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 250;
        nModifierUpdateBlock = 50;

        nBlockStakeModifierlV2 = 1967000;

        nSupplyBeforeFakeSerial = 0;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "U.S. News & World Report Jan 28 2016 With His Absence, Trump Dominates Another Debate";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 2402015;

        CDataStream stream(ParseHex("010000000000000000000000000000000000000000000000000000000000000000000000cbac770aa589bb71f32b958070dbee3c97d71572a96a825bc60e1e0faf6b955568a6d95df0ff0f1e67f010000101000000010000000000000000000000000000000000000000000000000000000000000000ffffffff1704ffff001d01040f414c514f202d203234313132303139ffffffff01000000000000000043410457c56ed69a1f42398804504fcab82f430cc864c8fc8cd25b76e141d12c13012ee9d500e11f84d5f75f5c669e88ca196142ddb7406d3635d840fa5e9d2a6bb100ac00000000"), SER_NETWORK, PROTOCOL_VERSION);
        stream >> genesis;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256S("000000b8486c11f11b0970584997554e317521b37a4673bcd551bebee593d294"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 211);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strObfuscationPoolDummyAddress = "aixE2v6zn2e2pznDKoAPvii17MmbkdLjHS";
        nStartMasternodePayments = genesis.nTime + 5400;


        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;

static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
