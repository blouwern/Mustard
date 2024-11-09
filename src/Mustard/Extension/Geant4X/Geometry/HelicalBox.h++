#pragma once

#include "G4Point3D.hh"
#include "G4TessellatedSolid.hh"
#include "G4ThreeVector.hh"

#include <string>

namespace Mustard::inline Extension::Geant4X::inline Geometry {

class HelicalBox : public G4TessellatedSolid {
public:
    HelicalBox(std::string name,
               double radius,             /* mm */
               double width,              /* mm */
               double pitch,              /* rad */
               double phi0,               /* rad */
               double phiTotal,           /* rad */
               double tolerance = 0.001); /* 1 */

    auto Radius() const -> auto { return fRadius; }
    auto Width() const -> auto { return fWidth; }
    auto Pitch() const -> auto { return fPitch; }
    auto Phi0() const -> auto { return fPhi0; }
    auto PhiTotal() const -> auto { return fPhiTotal; }
    auto Tolerance() const -> auto { return fTolerance; }

    auto TotalLength() const -> auto { return fTotalLength; }
    auto ZLength() const -> auto { return fZLength; }
    auto FrontEndPosition() const -> auto { return fFrontEndPosition; }
    auto FrontEndNormal() const -> auto { return fFrontEndNormal; }
    auto BackEndPosition() const -> auto { return fBackEndPosition; }
    auto BackEndNormal() const -> auto { return fBackEndNormal; }

    auto GetEntityType() const -> G4GeometryType override { return "G4XHelicalBox"; }

private:
    double fRadius;
    double fWidth;
    double fPitch;
    double fPhi0;
    double fPhiTotal;
    double fTolerance;

    double fTotalLength;
    double fZLength;
    G4Point3D fFrontEndPosition;
    G4ThreeVector fFrontEndNormal;
    G4Point3D fBackEndPosition;
    G4ThreeVector fBackEndNormal;
};

} // namespace Mustard::inline Extension::Geant4X::inline Geometry
