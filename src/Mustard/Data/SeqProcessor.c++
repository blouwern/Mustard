// -*- C++ -*-
//
// Copyright 2020-2024  The Mustard development team
//
// This file is part of Mustard, an offline software framework for HEP experiments.
//
// Mustard is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Mustard is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Mustard. If not, see <https://www.gnu.org/licenses/>.

#include "Mustard/Data/SeqProcessor.h++"

namespace Mustard::Data {

SeqProcessor::SeqProcessor() :
    ProcessorBase{},
    fPrintProgress{true},
    fProgressBar{} {}

auto SeqProcessor::LoopBeginAction(Index nTotal) -> void {
    if (fPrintProgress) {
        fProgressBar.Start(nTotal);
    }
}

auto SeqProcessor::IterationEndAction() -> void {
    if (fPrintProgress) {
        fProgressBar.Tick();
    }
}

auto SeqProcessor::LoopEndAction() -> void {
    if (fPrintProgress) {
        fProgressBar.Complete();
    }
}

} // namespace Mustard::Data
