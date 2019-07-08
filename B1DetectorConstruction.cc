//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#define L 5

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 30*cm, env_sizeZ = 40*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
  new G4Box("World",                       //its name
  0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
  new G4LogicalVolume(solidWorld,          //its solid
    world_mat,           //its material
    "World");            //its name

    G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
      G4ThreeVector(),       //at (0,0,0)
      logicWorld,            //its logical volume
      "World",               //its name
      0,                     //its mother  volume
      false,                 //no boolean operation
      0,                     //copy number
      checkOverlaps);        //overlaps checking

      //
      // Envelope
      //
      G4Box* solidEnv =
      new G4Box("Envelope",                    //its name
      0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

      G4LogicalVolume* logicEnv =
      new G4LogicalVolume(solidEnv,            //its solid
        env_mat,             //its material
        "Envelope");         //its name

        new G4PVPlacement(0,                       //no rotation
          G4ThreeVector(),         //at (0,0,0)
          logicEnv,                //its logical volume
          "Envelope",              //its name
          logicWorld,              //its mother  volume
          false,                   //no boolean operation
          0,                       //copy number
          checkOverlaps);          //overlaps checking



          //
          // Shape 1
          //
          G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
          G4ThreeVector pos1 = G4ThreeVector(0, 0*cm, -13*cm);  //in or out, up or down, left or right

          // Box shape
          G4double shape1_pX = L*cm;    //left and right
          G4double shape1_pY = L*2*cm;   //up and down
          G4double shape1_pZ = 1*cm;   //toward and away
          G4Box* solidShape1 =
          new G4Box("Shape1",                           //its name
          shape1_pX, shape1_pY, shape1_pZ);		//size

        G4LogicalVolume* logicShape1 =
        new G4LogicalVolume(solidShape1,         //its solid
          shape1_mat,          //its material
          "Shape1");           //its name

          new G4PVPlacement(0,                       //no rotation
            pos1,                    //at position
            logicShape1,             //its logical volume
            "Shape1",                //its name
            logicEnv,                //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking


            //shape 2
            G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
            G4ThreeVector pos2 = G4ThreeVector(0, 9*cm, -9.5*cm); //in or out, up or down, left or right

            // box
            G4double shape2_pX = L*cm;              //left and right
            G4double shape2_pY = L/3*cm;             //up and down
            G4double shape2_pZ = L/1.8*cm;             //toward and away
            

	    G4Box* solidShape2 =
            new G4Box("Shape2",                               //its name
            shape2_pX,shape2_pY,shape2_pZ                     //its size
          );

          G4LogicalVolume* logicShape2 =
          new G4LogicalVolume(solidShape2,         //its solid
            shape2_mat,          //its material
            "Shape2");           //its name

            new G4PVPlacement(0,                       //no rotation
              pos2,                    //at position
              logicShape2,             //its logical volume
              "Shape2",                //its name
              logicEnv,                //its mother  volume
              false,                   //no boolean operation
              0,                       //copy number
              checkOverlaps);          //overlaps checking


		//shape 3
	    G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
            G4ThreeVector pos3 = G4ThreeVector(0, 3*cm, -9.5*cm); //in or out, up or down, left or right

            // Box
            G4double shape3_pX = L*cm;              //left and right
            G4double shape3_pY = L/3*cm;             //up and down
            G4double shape3_pZ  = L/1.8*cm;             //toward and away
            G4Box* solidShape3 =
            new G4Box("Shape3",                               //its name
            shape3_pX,shape3_pY,shape3_pZ                     //its size
          );

          G4LogicalVolume* logicShape3 =
          new G4LogicalVolume(solidShape3,         //its solid
            shape3_mat,          //its material
            "Shape3");           //its name

            new G4PVPlacement(0,                       //no rotation
              pos3,                    //at position
              logicShape3,             //its logical volume
              "Shape3",                //its name
              logicEnv,                //its mother  volume
              false,                   //no boolean operation
              0,                       //copy number
              checkOverlaps);          //overlaps checking



	    //shape 4
	  G4ThreeVector pos4 = G4ThreeVector(0, 0*cm, -4*cm);

	  new G4Box("Shape1",                               //its name
          shape1_pX,shape1_pY,shape1_pZ                     //its size
        );
        
        G4LogicalVolume* logicShape4 =
        new G4LogicalVolume(solidShape1,         //its solid
          shape1_mat,          //its material
          "Shape4");           //its name
          
          new G4PVPlacement(0,                       //no rotation
            pos4,                    //at position
            logicShape4,             //its logical volume
            "Shape4",                //its name
            logicEnv,                //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking	   

	
	  //shape 5
	G4ThreeVector pos5 = G4ThreeVector(0, 0*cm, 0*cm);
	
	new G4Box("Shape5",shape1_pX,shape1_pY,shape1_pZ);

	G4LogicalVolume* logicShape5 = new G4LogicalVolume(solidShape1,shape1_mat,"shape4");

	new G4PVPlacement(0,pos5, logicShape5,"shape5",logicEnv, false,0,checkOverlaps);
	

	 //shape 6
         G4ThreeVector pos6 = G4ThreeVector(0, 0*cm, 9*cm);

        new G4Box("Shape6",shape1_pX,shape1_pY,shape1_pZ);

        G4LogicalVolume* logicShape6 = new G4LogicalVolume(solidShape1,shape1_mat,"shape4");

        new G4PVPlacement(0,pos6, logicShape6,"shape6",logicEnv, false,0,checkOverlaps);

	//shape 7 
        G4ThreeVector pos7 = G4ThreeVector(0, 9*cm, 12*cm);

        new G4Box("Shape7",shape2_pX,shape2_pY,shape2_pZ);

        G4LogicalVolume* logicShape7 = new G4LogicalVolume(solidShape2,shape2_mat,"shape7");

        new G4PVPlacement(0,pos7, logicShape7,"shape7",logicEnv, false,0,checkOverlaps);

	//shape 8
	G4ThreeVector pos8= G4ThreeVector(0, 0*cm , 12*cm);
	new G4Box("Shape 8",shape2_pX,shape2_pY,shape2_pZ);
	G4LogicalVolume* logicShape8 = new G4LogicalVolume(solidShape2,shape2_mat, "shape8");
	new G4PVPlacement(0,pos8,logicShape8, "shape8", logicEnv,false,0,checkOverlaps);

	//shape 9
	G4ThreeVector pos9 = G4ThreeVector(0, -9 *cm,12*cm);
	new G4Box("Shape 9", shape2_pX, shape2_pY,shape2_pZ);
	G4LogicalVolume* logicShape9 = new G4LogicalVolume(solidShape2,shape2_mat,"shape9");
	new G4PVPlacement(0,pos9,logicShape9,"shape9",logicEnv,false,0,checkOverlaps);
	
	//shape10
	G4ThreeVector pos10 = G4ThreeVector(0, 9 *cm,2.8*cm);
	new G4Box("Shape 9", shape2_pX, shape2_pY,shape2_pZ);
	G4LogicalVolume* logicShape10 = new G4LogicalVolume(solidShape2,shape2_mat,"shape9");
	new G4PVPlacement(0,pos10,logicShape10,"shape9",logicEnv,false,0,checkOverlaps);
	

	//shape11
	G4ThreeVector pos11 = G4ThreeVector(0, 1*cm,3.8*cm);
	new G4Box("Shape 11", shape2_pX, shape2_pY,shape2_pZ);
	G4LogicalVolume* logicShape11 = new G4LogicalVolume(solidShape2,shape2_mat,"shape9");
	new G4PVPlacement(0,pos11,logicShape11,"shape9",logicEnv,false,0,checkOverlaps);

	//shape 12
	  G4Material* shape12_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
          G4ThreeVector pos12 = G4ThreeVector(0, 4.5*cm, 4.6*cm);  //in or out, up or down, left or right

          G4double shape12_pX = L*cm;    //left and right
          G4double shape12_pY = L/1.2*cm;   //up and down
          G4double shape12_pZ  = (L/(double)5)*cm;   //toward and away
          G4Box* solidShape12 =
          new G4Box("Shape12",                               //its name
          shape12_pX,shape12_pY,shape12_pZ                     //its size
        );

        G4LogicalVolume* logicShape12 =
        new G4LogicalVolume(solidShape12,         //its solid
          shape12_mat,          //its material
          "Shape12");           //its name

          new G4PVPlacement(0,                       //no rotation
            pos12,                    //at position
            logicShape12,             //its logical volume
            "Shape12",                //its name
            logicEnv,                //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking

	//shape 13
	G4Material* shape13_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
          G4ThreeVector pos13 = G4ThreeVector(0, -5*cm, 5.7*cm);  //in or out, up or down, left or right

          // Trapezoid shape
          G4double shape13_pX = L*cm;    //left and right
          G4double shape13_pY = L*cm;   //up and down
          G4double shape13_pZ = (L/(double)5)*cm;   //toward and away
          G4Box* solidShape13 =
          new G4Box("Shape13",                               //its name
          shape13_pX,shape13_pY,shape13_pZ                     //its size
        );

        G4LogicalVolume* logicShape13 =
        new G4LogicalVolume(solidShape13,         //its solid
          shape13_mat,          //its material
          "Shape13");           //its name

          new G4PVPlacement(0,                       //no rotation
            pos13,                    //at position
            logicShape13,             //its logical volume
            "Shape13",                //its name
            logicEnv,                //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking
              // Set Shape2 as scoring volume
              //
              fScoringVolume = logicShape13;

              //
              //always return the physical World
              //
              return physWorld;
            }

            //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

