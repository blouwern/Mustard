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

#pragma once

#include "Mustard/Extension/Geant4X/Particle/Antimuonium.h++"
#include "Mustard/Extension/Geant4X/Particle/Muonium.h++"
#include "Mustard/Extension/Geant4X/Physics/TargetForMuoniumPhysics.h++"
#include "Mustard/Extension/Geant4X/Process/MuoniumFormation.h++"
#include "Mustard/Extension/Geant4X/Process/MuoniumTransport.h++"
#include "Mustard/Utility/NonMoveableBase.h++"

#include "G4EmBuilder.hh"
#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"
#include "G4VPhysicsConstructor.hh"

namespace Mustard::inline Extension::Geant4X::inline Physics {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysics final : public NonMoveableBase,
                             public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose);

    auto ConstructParticle() -> void override;
    auto ConstructProcess() -> void override;
};

} // namespace Mustard::inline Extension::Geant4X::inline Physics

#include "Mustard/Extension/Geant4X/Physics/MuoniumPhysics.inl"
