/**
 * @file StopWatch.h
 * @brief My utility of stop watch
 * @author Keren Zhu
 * @date 04/01/2020
 */

#ifndef KLIB_STOPWATCH_HPP_
#define KLIB_STOPWATCH_HPP_

#include <chrono>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Assert.h"
#include "MsgPrinter.h"
#include <iostream>

namespace klib
{
    class StopWatch;
    /// @brief class for maintain the global stop watch
    class StopWatchMgr
    {
        public:
            static std::shared_ptr<StopWatch> createNewStopWatch(const std::string &name);
            static void recordTime(std::uint64_t time, std::uint32_t idx)
            {
                _us[idx] = time;
            }
            static std::uint64_t time(const std::string &name)
            {
                auto iter = _nameToIdxMap.find(name);
                //AssertMsg(iter != _nameToIdxMap.end(), "Did not found the stop watch with name %s \n", name.c_str());
                //Assert(iter != _nameToIdxMap.end());
                return _us[iter->second];
            }
            /// @brief start the default timer. The time will return on the end, and won't be recorded
            static void quickStart();
            /// @brief end the default timer.
            /// @return the time since start
            static uint64_t quickEnd();

        private:
            static std::vector<std::uint64_t> _us; // The record of the stop watch times
            static std::unordered_map<std::string, std::uint32_t> _nameToIdxMap; ///< Map timer names to indices
            static StopWatch _watch; ///< The default one for quick usage that don't need to record
    };
    /// @brief the single stop watch
    class StopWatch
    {
        public:
            StopWatch(std::uint32_t idx) : _idx(idx) { _count = false; start(); _us = 0; }
            ~StopWatch()
            {
                stop();
                StopWatchMgr::recordTime(_us, _idx);
            }
            void stop()
            {
                if (_count == false) { return; }
                _us += curTime();
                _count = false;
            }
            void start()
            {
                if (_count == true) { return; } 
                _last = std::chrono::high_resolution_clock::now(); 
                _count = true;
            }
            std::uint64_t curTime()
            {
                return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _last).count();
            }
            std::uint64_t record()
            {
                return _us;
            }
            void clear()
            {
                _us = 0;
                _count = false;
            }
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> _last;
            bool _count = false;
            std::uint64_t _us; ///< total microsecond
            std::uint32_t _idx; ///< The index in mgr
    };
};
#endif //KLIB_STOPWATCH_HPP_
