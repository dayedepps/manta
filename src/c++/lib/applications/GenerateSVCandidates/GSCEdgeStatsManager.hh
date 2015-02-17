// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Manta
// Copyright (c) 2013-2014 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/sequencing/licenses/>
//

///
/// \author Chris Saunders
///

#pragma once

#include "EdgeRuntimeTracker.hh"
#include "svgraph/GSCEdgeStats.hh"
#include "svgraph/EdgeInfo.hh"

#include "boost/utility.hpp"

#include <iosfwd>
#include <string>


/// handles all messy real world interaction for the stats module,
/// stats module itself just accumulates data and
///
struct GSCEdgeStatsManager : private boost::noncopyable
{
    GSCEdgeStatsManager(
        const std::string& outputFile);

    ~GSCEdgeStatsManager();

    void
    update(
        const EdgeInfo& edge,
        const EdgeRuntimeTracker& edgeTracker)
    {
        if (_osPtr == nullptr) return;

        GSCEdgeGroupStats& gStats(getStatsGroup(edge));
        gStats.totalEdgeCount += 1;
        gStats.totalTime += edgeTracker.getLastEdgeTime();
        gStats.assemblyTime += edgeTracker.assmTime.getSeconds();
        gStats.scoringTime += edgeTracker.scoreTime.getSeconds();
    }

private:
    GSCEdgeGroupStats&
    getStatsGroup(
        const EdgeInfo& edge)
    {
        return (edge.isSelfEdge() ? edgeStats.data.selfEdges : edgeStats.data.remoteEdges);
    }

    std::ostream* _osPtr;
    GSCEdgeStats edgeStats;
};
