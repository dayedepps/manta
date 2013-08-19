// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Manta
// Copyright (c) 2013 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/downloads/sequencing/licenses/>.
//

///
/// \author Chris Saunders

#pragma once

#include "assembly/AssembledContig.hh"
#include "alignment/GlobalJumpAligner.hh"
#include "blt_util/reference_contig_segment.hh"
#include "manta/SVCandidate.hh"

#include <vector>


/// Assembly data pertaining to a specific SV candidate
///
/// Assembly starts from a low-resolution SV candidate. This holds
/// any persistent data related to the assembly process, such as data
/// useful for scoring the candidate.
///
/// As a future design note -- it may be possible that the candidate is broken
/// into multiple candidates during assembly-based hypothesis refinement, so
/// this struct may cover multiple refined candidates (but always only one input
/// candidate.
///
struct SVCandidateAssemblyData
{
    SVCandidateAssemblyData() :
        isBestAlignment(false),
        bestAlignmentIndex(0)
    {}

    void
    clear()
    {
        contigs.clear();
        alignments.clear();
        isBestAlignment=false;
        bestAlignmentIndex=0;
        bp1ref.clear();
        bp2ref.clear();
    }

    typedef JumpAlignmentResult<int> JumpAlignmentResultType;

    Assembly contigs; ///< assembled contigs for both breakpoints
    std::vector<JumpAlignmentResultType> alignments; ///< contig alignments, one per contig, may be empty

    bool isBestAlignment;        ///< is there a contig/alignment good enough to be used for reporting?
    unsigned bestAlignmentIndex; ///< if isBestAlignment, which is the best?

    // expanded reference regions around the candidate SV breakend regions:
    reference_contig_segment bp1ref;
    reference_contig_segment bp2ref;

    SVCandidate sv; ///< if isBestAlignment, summarize refined sv candidate
};
