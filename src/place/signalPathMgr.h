/**
 * @file signalPathMgr.h
 * @brief The placement database data structure
 * @author Keren Zhu
 * @date 02/25/2020
 */

#ifndef IDEAPLACE_SIGALPATHMGR_H_
#define IDEAPLACE_SIGALPATHMGR_H_

#include "db/Database.h"

PROJECT_NAMESPACE_BEGIN

/// @brief the decomposed signal path segment. It will contain four pins and involves three cells
class SigPathSeg
{
    public:
        explicit SigPathSeg() = default;
        explicit SigPathSeg(IndexType sPinIdx, IndexType midPinIdxA, IndexType midPinIdxB, IndexType tPinIdx)
            : _sPinIdx(sPinIdx), _midPinIdxA(midPinIdxA), _midPinIdxB(midPinIdxB), _tPinIdx(tPinIdx)
        {}
        /// @brief get the starting pin of the first segment
        IndexType beginPinFirstSeg() const { return _sPinIdx; }
        /// @brief get the ending pin of the first segment
        IndexType endPinFirstSeg() const { return _midPinIdxA; }
        /// @brief get the starting pin of the second segment
        IndexType beginPinSecondSeg() const { return _midPinIdxB; }
        /// @brief get the ending pin of the second segment
        IndexType endPinSecondSeg() const { return _tPinIdx; }
    private:
        IndexType _sPinIdx = INDEX_TYPE_MAX; ///< The starting pin index of the first segment. It belongs to cell 1,
        IndexType _midPinIdxA = INDEX_TYPE_MAX; ///< The ending pin index of the first segment. It belongs to cell 2.
        IndexType _midPinIdxB = INDEX_TYPE_MAX; ///< The starting pin index of the second segment. It belongs to cell 2.
        IndexType _tPinIdx = INDEX_TYPE_MAX; ///< The ending pin index of the second segment. It belongs to cell 3.
};

/// @brief the signal path manager
class SigPathMgr
{
    public:
        /// @brief constructor
        /// @param the placement database
        explicit SigPathMgr(Database &db);
        /// @brief get the segment list
        const std::vector<SigPathSeg> vSegList() const { return _segs; }
    private:
        void decomposeSignalPaths();
    private:
        Database &_db;
        std::vector<SigPathSeg> _segs; ///< The decomposed segments
};

PROJECT_NAMESPACE_END

#endif //IDEAPLACE_SIGALPATHMGR_H_