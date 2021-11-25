//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 28 14:51:58 2021 by ROOT version 6.24/00
// from TTree Events/Events
// found on file: LWSM200DnR.root
//////////////////////////////////////////////////////////

#ifndef Gen_h
#define Gen_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "Math/GenVector/Cartesian3D.h"

class Gen {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxGenPart_vertex = 25;

   // Declaration of leaf types
   Int_t           numGenPart;
   vector<float>   *GenPart_pt;
   vector<float>   *GenPart_eta;
   vector<float>   *GenPart_mass;
   vector<int>     *GenPart_pdgId;
   vector<int>     *GenPart_mompdgId;
   vector<float>   *GenPart_phi;
   vector<float>   *GenPart_px;
   vector<float>   *GenPart_py;
   vector<float>   *GenPart_pz;
   vector<int>     *GenPart_status;
   vector<bool>    *GenPart_longlived;
   Int_t           GenPart_vertex_;
   Double_t        GenPart_vertex_fCoordinates_fX[kMaxGenPart_vertex];   //[GenPart_vertex_]
   Double_t        GenPart_vertex_fCoordinates_fY[kMaxGenPart_vertex];   //[GenPart_vertex_]
   Double_t        GenPart_vertex_fCoordinates_fZ[kMaxGenPart_vertex];   //[GenPart_vertex_]
   Int_t           numGenDau;
   vector<float>   *GenDau_pt;
   vector<float>   *GenDau_eta;
   vector<float>   *GenDau_mass;
   vector<int>     *GenDau_pdgId;
   vector<int>     *GenDau_mompdgId;
   vector<float>   *GenDau_phi;
   vector<float>   *GenDau_px;
   vector<float>   *GenDau_py;
   vector<float>   *GenDau_pz;
   vector<int>     *GenDau_status;
   vector<bool>    *GenDau_longlived;

   // List of branches
   TBranch        *b_numGenPart;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_mass;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_mompdgId;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_px;   //!
   TBranch        *b_GenPart_py;   //!
   TBranch        *b_GenPart_pz;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_longlived;   //!
   TBranch        *b_GenPart_vertex_;   //!
   TBranch        *b_GenPart_vertex_fCoordinates_fX;   //!
   TBranch        *b_GenPart_vertex_fCoordinates_fY;   //!
   TBranch        *b_GenPart_vertex_fCoordinates_fZ;   //!
   TBranch        *b_numGenDau;   //!
   TBranch        *b_GenDau_pt;   //!
   TBranch        *b_GenDau_eta;   //!
   TBranch        *b_GenDau_mass;   //!
   TBranch        *b_GenDau_pdgId;   //!
   TBranch        *b_GenDau_mompdgId;   //!
   TBranch        *b_GenDau_phi;   //!
   TBranch        *b_GenDau_px;   //!
   TBranch        *b_GenDau_py;   //!
   TBranch        *b_GenDau_pz;   //!
   TBranch        *b_GenDau_status;   //!
   TBranch        *b_GenDau_longlived;   //!

   Gen(TTree *tree=0);
   virtual ~Gen();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Gen_cxx
Gen::Gen(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("LWSM200DnR.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("LWSM200DnR.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("LWSM200DnR.root:/mygenparticle");
      dir->GetObject("Events",tree);

   }
   Init(tree);
}

Gen::~Gen()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Gen::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Gen::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Gen::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   GenPart_pt = 0;
   GenPart_eta = 0;
   GenPart_mass = 0;
   GenPart_pdgId = 0;
   GenPart_mompdgId = 0;
   GenPart_phi = 0;
   GenPart_px = 0;
   GenPart_py = 0;
   GenPart_pz = 0;
   GenPart_status = 0;
   GenPart_longlived = 0;
   GenDau_pt = 0;
   GenDau_eta = 0;
   GenDau_mass = 0;
   GenDau_pdgId = 0;
   GenDau_mompdgId = 0;
   GenDau_phi = 0;
   GenDau_px = 0;
   GenDau_py = 0;
   GenDau_pz = 0;
   GenDau_status = 0;
   GenDau_longlived = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("numGenPart", &numGenPart, &b_numGenPart);
   fChain->SetBranchAddress("GenPart_pt", &GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta", &GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_mass", &GenPart_mass, &b_GenPart_mass);
   fChain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId", &GenPart_mompdgId, &b_GenPart_mompdgId);
   fChain->SetBranchAddress("GenPart_phi", &GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_px", &GenPart_px, &b_GenPart_px);
   fChain->SetBranchAddress("GenPart_py", &GenPart_py, &b_GenPart_py);
   fChain->SetBranchAddress("GenPart_pz", &GenPart_pz, &b_GenPart_pz);
   fChain->SetBranchAddress("GenPart_status", &GenPart_status, &b_GenPart_status);
   fChain->SetBranchAddress("GenPart_longlived", &GenPart_longlived, &b_GenPart_longlived);
   fChain->SetBranchAddress("GenPart_vertex", &GenPart_vertex_, &b_GenPart_vertex_);
   fChain->SetBranchAddress("GenPart_vertex.fCoordinates.fX", GenPart_vertex_fCoordinates_fX, &b_GenPart_vertex_fCoordinates_fX);
   fChain->SetBranchAddress("GenPart_vertex.fCoordinates.fY", GenPart_vertex_fCoordinates_fY, &b_GenPart_vertex_fCoordinates_fY);
   fChain->SetBranchAddress("GenPart_vertex.fCoordinates.fZ", GenPart_vertex_fCoordinates_fZ, &b_GenPart_vertex_fCoordinates_fZ);
   fChain->SetBranchAddress("numGenDau", &numGenDau, &b_numGenDau);
   fChain->SetBranchAddress("GenDau_pt", &GenDau_pt, &b_GenDau_pt);
   fChain->SetBranchAddress("GenDau_eta", &GenDau_eta, &b_GenDau_eta);
   fChain->SetBranchAddress("GenDau_mass", &GenDau_mass, &b_GenDau_mass);
   fChain->SetBranchAddress("GenDau_pdgId", &GenDau_pdgId, &b_GenDau_pdgId);
   fChain->SetBranchAddress("GenDau_mompdgId", &GenDau_mompdgId, &b_GenDau_mompdgId);
   fChain->SetBranchAddress("GenDau_phi", &GenDau_phi, &b_GenDau_phi);
   fChain->SetBranchAddress("GenDau_px", &GenDau_px, &b_GenDau_px);
   fChain->SetBranchAddress("GenDau_py", &GenDau_py, &b_GenDau_py);
   fChain->SetBranchAddress("GenDau_pz", &GenDau_pz, &b_GenDau_pz);
   fChain->SetBranchAddress("GenDau_status", &GenDau_status, &b_GenDau_status);
   fChain->SetBranchAddress("GenDau_longlived", &GenDau_longlived, &b_GenDau_longlived);
   Notify();
}

Bool_t Gen::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Gen::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Gen::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Gen_cxx
