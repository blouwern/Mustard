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

#include "Mustard/Extension/Geant4X/Physics/MuoniumRareDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumRareDecayPhysicsMessenger.h++"

#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

namespace Mustard::inline Extension::Geant4X::inline Physics {

MuoniumRareDecayPhysicsMessenger::MuoniumRareDecayPhysicsMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fDoubleRadiativeDecayBR{},
    fElectronPairDecayBR{},
    fUpdateDecayBR{} {

    fDirectory = std::make_unique<G4UIdirectory>("/Mustard/Physics/MuoniumDecay/");
    fDirectory->SetGuidance("About muonium rare decay channel and decay generators.");

    fDoubleRadiativeDecayBR = std::make_unique<G4UIcmdWithADouble>("/Mustard/Physics/MuoniumDecay/DoubleRadiativeDecay/BR", this);
    fDoubleRadiativeDecayBR->SetGuidance("Set branching ratio for muonium double radiative decay channel.");
    fDoubleRadiativeDecayBR->SetParameterName("BR", false);
    fDoubleRadiativeDecayBR->SetRange("0 <= BR && BR <= 1");
    fDoubleRadiativeDecayBR->AvailableForStates(G4State_PreInit, G4State_Idle);

    fElectronPairDecayBR = std::make_unique<G4UIcmdWithADouble>("/Mustard/Physics/MuoniumDecay/ElectronPairDecay/BR", this);
    fElectronPairDecayBR->SetGuidance("Set branching ratio for muonium pair production decay channel.");
    fElectronPairDecayBR->SetParameterName("BR", false);
    fElectronPairDecayBR->SetRange("0 <= BR && BR <= 1");
    fElectronPairDecayBR->AvailableForStates(G4State_PreInit, G4State_Idle);

    fUpdateDecayBR = std::make_unique<G4UIcmdWithoutParameter>("/Mustard/Physics/MuoniumDecay/UpdateDecayBR", this);
    fUpdateDecayBR->SetGuidance("Update decay branching ratio.");
    fUpdateDecayBR->AvailableForStates(G4State_Idle);
}

MuoniumRareDecayPhysicsMessenger::~MuoniumRareDecayPhysicsMessenger() = default;

auto MuoniumRareDecayPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fDoubleRadiativeDecayBR.get()) {
        Deliver<MuoniumRareDecayPhysics>([&](auto&& r) {
            r.DoubleRadiativeDecayBR(fDoubleRadiativeDecayBR->GetNewDoubleValue(value));
        });
    } else if (command == fElectronPairDecayBR.get()) {
        Deliver<MuoniumRareDecayPhysics>([&](auto&& r) {
            r.ElectronPairDecayBR(fElectronPairDecayBR->GetNewDoubleValue(value));
        });
    } else if (command == fUpdateDecayBR.get()) {
        Deliver<MuoniumRareDecayPhysics>([&](auto&& r) {
            r.UpdateDecayBR();
        });
    }
}

} // namespace Mustard::inline Extension::Geant4X::inline Physics