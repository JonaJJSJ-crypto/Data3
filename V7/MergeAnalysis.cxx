/////secvecstudy

// g++ -std=c++11 -g -O3 -Wall -Wextra -o MergeAnalysis MergeAnalysis.cxx $(root-config --cflags --libs)
//Include ROOT classes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TLatex.h"
#include "TStopwatch.h"
#include <Math/GenVector/PositionVector3D.h>
//Include C++ classes
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
using namespace ROOT::Math;

/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
/*TH1F* LW200electron_num = new TH1F("LW200electron_num","number of events with elec/phot pt>20GeV",10,0,10);
TH1F* LW200electron_pt = new TH1F("LW200electron_pt","Electrons pt for missing trigg",100,0,200);
TH1F* LW200electron_dxy = new TH1F("LW200electron_dxy","Electrons pt for missing trigg",100,-0.5,0.5);
TH1F* LW200electron_dz = new TH1F("LW200electron_dz","Electrons pt for missing trigg",200,-10,10);
TH1F* LW200electron_eta = new TH1F("LW200electron_eta","Electrons eta for missing trigg",100,-5,5);
TH1F* LW200SGenele_num = new TH1F("LW200SGenele_num","Number of signal gen-electrons per event (pt<15GeV)",3,0,3);
TH1F* LW200SGenele_pt = new TH1F("LW200SGenele_pt","Signal Genele pt ",100,0,200);
TH1F* LW200SGenele_dxy = new TH1F("LW200SGenele_dxy","Signal Genele pt ",100,-0.5,0.5);
TH1F* LW200SGenele_dz = new TH1F("LW200SGenele_dz","Signal Genele pt ",200,-10,10);
TH1F* LW200SGenele_eta = new TH1F("LW200SGenele_eta","Signal Genele eta",100,-5,5);
TH1F* LW200Genelec_num = new TH1F("LW200Genelec_num","number of gen-electrons",50,0,100);
TH1F* LW200Genelec_pt = new TH1F("LW200Genelec_pt","Genelec pt",100,0,200);
TH1F* LW200Genelec_eta = new TH1F("LW200Genelec_eta","Genelec eta",100,-5,5);
TH1F* LW200GenZdau_pt = new TH1F("LW200GenZdau_pt","GensZdau pt for missing trigg",100,0,200);
TH1F* LW200GenZdau_eta = new TH1F("LW200GenZdau_eta","GensZdau eta for missing trigg",100,-5,5);
TH1F* LW200Genelec_disp = new TH1F("LW200Generated_electron_Bmatch","Gen Electron secondary vertex displacement",200,0,1);
TH1F* LW200EleBsecvec = new TH1F("LW200Electron_Bmatch","Best matched secondary vertex displacement",200,0,1);
TH1F* LW200Genelec_disp_f = new TH1F("LW200Generated_electron_Bmatch Filtered","Gen Electron secondary vertex displacement filtered",200,0,1);
TH1F* LW200EleBsecvec_f = new TH1F("LW200Electron_Bmatch_Filtered","Best matched secondary vertex displacement filtered",200,0,1);
TH1F* LW200TrigObj = new TH1F("LW200TriggerObject_Electrons","Number of electrons and trigger Object matching",2,0,2);
TH1F* LW200TrigObjDR = new TH1F("LW200TriggerObject_Electrons_DR","Number of electrons and trigger Object matching deltaR",200,0,4);*/
TH1F* LW200SecVec_pos = new TH1F("LW200SecVec_pos","Secvec pair is Mergeable",2,0,2);
TH1F* LW200SecVec_dist = new TH1F("LW200SecVec_dist","Secvec pair distance",100,0,0.2);
TH1F* LW200SecVec_errorx = new TH1F("LW200SecVec_errorx","Secvec Errorx distribution",100,0,0.021);
TH1F* LW200SecVec_errory = new TH1F("LW200SecVec_errory","Secvec Errory distribution",100,0,0.021);
TH1F* LW200SecVec_errorz = new TH1F("LW200SecVec_errorz","Secvec Errorz distribution",100,0,0.021);
TH1F* LW200SecVec_num = new TH1F("LW200SecVec_num","Secvec Number of mergeable vertices per event",100,0,30000);
TH1F* LW200SecVec_dR = new TH1F("LW200SecVec_dR","Secvec Seed track dR",100,0,1);
TH1F* LW200SecVec_dR1 = new TH1F("LW200SecVec_dR1","Secvec Aux track 1 dR",100,0,1);
TH1F* LW200SecVec_dR2 = new TH1F("LW200SecVec_dR2","Secvec Aux track 2 dR",100,0,1);
TH1F* LW200SecVec_TrkHQ= new TH1F("LW200SecVec_TrkHQ","Signal electrons quality",3,-1,2);
TH1F* LW200SecVec_HQElept= new TH1F("LW200SecVec_HQElept","HQ electrons pt",100,0,200);
TH1F* LW200SecVec_HQTrkpt= new TH1F("LW200SecVec_HQTrkpt","HQ electrontrack pt",100,0,200);
TH2F* LW200SecVec_XYGen;
TH2F* LW200SecVec_XYSignal1;
TH2F* LW200SecVec_XYSignal2;
TH2F* LW200SecVec_XYSignal3;
TH2F* LW200SecVec_XYSignal4;
TH2F* LW200SecVec_XY;
TH2F* LW200SecVec_XY_P;
//TH2F* LW200SecVec_XY = new TH2F("LW200SecVec_XY","SecVec XY Distribution",20,-10,10,20,-10,10);

const std::string samplesBasePath = "";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 12;
const int Minpt = 14;

//Histograms for signal region


//Requiered trigger
string triggerRequest[] = {"HLT_Photon26_Photon18"};

// Fixed size dimensions of array or collections stored in the TTree if any.


class EventLoopAnalysisTemplate {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *tevents;
  TTree          *ttrigger;
  TTree          *telectrons;
  TTree          *tvertex;
  TTree          *tphotons;
  TTree          *tGenPart;
  TTree          *tTrack;
  TTree          *tjets;
  TTree          *ttrigobjs;


  Int_t           fCurrent; //!current Tree number in a TChain
  TString          labeltag;
  TString         filename;
  Float_t          theweight;
  Long64_t         Triggcount;

  //array to keep histograms to be written and easily loop over them
  TH1F            *hists[nhists];

  // Declaration of example leaf types
  Int_t           run;
  UInt_t          luminosityBlock;
  ULong64_t	      event;
  std::map<std::string, int> *triggermap;
  vector<float>   *PV_x;
  vector<float>   *PV_y;
  vector<float>   *PV_z;
  vector<float>   *electron_pt;
  vector<float>   *electron_eta;
  vector<float>   *electron_phi;
  vector<float>   *electron_dxy;
  vector<float>   *electron_dz;
  vector<bool>   *electron_isLoose;
  vector<bool>   *electron_isMedium;
  vector<bool>   *electron_isTight;
  vector<int>   *trk_isHQ;
  vector<float>   *genelec_pt;
  vector<float>   *genelec_DRscore;
  //vector<float>   *electron_Bsecvec;
  //vector<float>   *secvec_deltaR;
  //vector<float>   *secvec_disp;
  vector<float>   *secvec_posx;
  vector<float>   *secvec_poserrorx;
  vector<float>   *secvec_posy;
  vector<float>   *secvec_poserrory;
  vector<float>   *secvec_posz;
  vector<float>   *secvec_poserrorz;
  vector<float>   *secvec_px;
  vector<float>   *secvec_py;
  vector<float>   *secvec_pz;
  vector<float>   *secvec_eta;
  vector<float>   *secvec_phi;
  vector<float>   *secvec_eta1;
  vector<float>   *secvec_phi1;
  vector<float>   *secvec_eta2;
  vector<float>   *secvec_phi2;
  vector<float>   *secvec_eleTag;
  vector<float>   *Esecvec_eleTag;
  vector<float>   *Esecvec_posx;
  vector<float>   *Esecvec_poserrorx;
  vector<float>   *Esecvec_posy;
  vector<float>   *Esecvec_poserrory;
  vector<float>   *Esecvec_posz;
  vector<float>   *Esecvec_poserrorz;
  vector<float>   *Esecvec_eta;
  vector<float>   *Esecvec_phi;
  vector<float>   *Esecvec_eta1;
  vector<float>   *Esecvec_phi1;
  vector<float>   *Esecvec_eta2;
  vector<float>   *Esecvec_phi2;
  vector<float>   *GenPart_pt;
  vector<float>   *GenPart_eta;
  vector<float>   *GenPart_phi;
  vector<float>   *GenPart_px;
  vector<float>   *GenPart_pdgId;
  vector<float>   *GenPart_mompdgId;
  vector<float>   *GenDau_pt;
  vector<float>   *GenDau_eta;
  vector<float>   *GenDau_phi;
  vector<float>   *GenDau_px;
  vector<float>   *GenDau_pdgId;
  vector<float>   *GenDau_mompdgId;
  vector<float>   *GenPart_vx;   //[GenPart_vertex_]
  vector<float>   *GenPart_vy;   //[GenPart_vertex_]
  vector<float>   *GenPart_vz;   //[GenPart_vertex_]
  vector<float>   *jet_pt;
  vector<float>   *trigobj_e;
  vector<float>   *trigobj_pt;
  vector<float>   *trigobj_pz;
  vector<float>   *trigobj_px;
  vector<float>   *trigobj_py;
  vector<float>   *trigobj_phi;
  vector<float>   *trigobj_eta;
  vector<float>   *Bsp_x;
  vector<float>   *Bsp_y;
  vector<float>   *Bsp_z;

  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_PV_x;   //!
  TBranch        *b_PV_y;   //!
  TBranch        *b_PV_z;   //!
  TBranch        *b_electron_pt;
  TBranch        *b_electron_eta;
  TBranch        *b_electron_phi;
  TBranch        *b_electron_dxy;
  TBranch        *b_electron_dz;
  TBranch        *b_electron_isLoose;
  TBranch        *b_electron_isMedium;
  TBranch        *b_electron_isTight;
  TBranch        *b_genelec_pt;
  TBranch        *b_genelec_DRscore;
  //TBranch        *b_electron_Bsecvec;
  //TBranch        *b_secvec_deltaR;
  //TBranch        *b_secvec_disp;
  TBranch        *b_secvec_posx;
  TBranch        *b_secvec_posy;
  TBranch        *b_secvec_posz;
  TBranch        *b_secvec_px;
  TBranch        *b_secvec_py;
  TBranch        *b_secvec_pz;
  TBranch        *b_secvec_phi;
  TBranch        *b_secvec_eta;
  TBranch        *b_secvec_phi1;
  TBranch        *b_secvec_eta1;
  TBranch        *b_secvec_phi2;
  TBranch        *b_secvec_eta2;
  TBranch        *b_secvec_poserrorx;
  TBranch        *b_secvec_poserrory;
  TBranch        *b_secvec_poserrorz;
  TBranch        *b_secvec_eleTag;
  TBranch        *b_Esecvec_eleTag;
  TBranch        *b_Esecvec_posx;
  TBranch        *b_Esecvec_posy;
  TBranch        *b_Esecvec_posz;
  TBranch        *b_Esecvec_phi;
  TBranch        *b_Esecvec_eta;
  TBranch        *b_Esecvec_phi1;
  TBranch        *b_Esecvec_eta1;
  TBranch        *b_Esecvec_phi2;
  TBranch        *b_Esecvec_eta2;
  TBranch        *b_Esecvec_poserrorx;
  TBranch        *b_Esecvec_poserrory;
  TBranch        *b_Esecvec_poserrorz;
  TBranch        *b_GenPart_pt;
  TBranch        *b_GenPart_eta;
  TBranch        *b_GenPart_phi;
  TBranch        *b_GenPart_px;
  TBranch        *b_GenPart_pdgId;
  TBranch        *b_GenPart_mompdgId;
  TBranch        *b_GenDau_pt;
  TBranch        *b_GenDau_eta;
  TBranch        *b_GenDau_phi;
  TBranch        *b_GenDau_px;
  TBranch        *b_GenDau_pdgId;
  TBranch        *b_GenDau_mompdgId;
  TBranch        *b_GenPart_vx;   //!
  TBranch        *b_GenPart_vy;   //!
  TBranch        *b_GenPart_vz;   //!
  TBranch        *b_jet_pt;
  TBranch        *b_trk_isHQ;
  TBranch        *b_trigobj_e;
  TBranch        *b_trigobj_pt;
  TBranch        *b_trigobj_pz;
  TBranch        *b_trigobj_px;
  TBranch        *b_trigobj_py;
  TBranch        *b_trigobj_eta;
  TBranch        *b_trigobj_phi;
  TBranch        *b_Bsp_x;
  TBranch        *b_Bsp_y;
  TBranch        *b_Bsp_z;

  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual float deltaR(float eta1, float phi1, float eta2, float phi2);
  void analysis();
  Float_t MinimalSelection(Int_t entry);

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;

  hists[0]=LW200SecVec_pos;
  hists[1]=LW200SecVec_dist;
  hists[2]=LW200SecVec_num;
  hists[3]=LW200SecVec_errorx;
  hists[4]=LW200SecVec_errory;
  hists[5]=LW200SecVec_errorz;
  hists[6]=LW200SecVec_dR;
  hists[7]=LW200SecVec_dR1;
  hists[8]=LW200SecVec_dR2;
  hists[9]=LW200SecVec_TrkHQ;
  hists[10]=LW200SecVec_HQElept;
  hists[11]=LW200SecVec_HQTrkpt;
  /*hists[1]=LW200electron_pt;
  hists[2]=LW200electron_eta;
  hists[3]=LW200SGenele_num;
  hists[4]=LW200SGenele_pt;
  hists[5]=LW200SGenele_eta;
  hists[6]=LW200GenZdau_pt;
  hists[7]=LW200GenZdau_eta;
  hists[8]=LW200Genelec_num;
  hists[9]=LW200Genelec_pt;
  hists[10]=LW200Genelec_eta;
  hists[11]=LW200Genelec_disp;
  hists[12]=LW200EleBsecvec;*/

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree* tree = 0;
   TFile *f = TFile::Open(filename);
   //trigger should go first as it is the more complicated one
   tree = (TTree*)f->Get("mytriggers/Events");
   //Get trees for friendship
   tevents = (TTree*)f->Get("myevents/Events");
   telectrons = (TTree*)f->Get("myelectrons/Events");
   tGenPart = (TTree*)f->Get("mygenparticle/Events");
   tjets = (TTree*)f->Get("myjets/Events");
   ttrigobjs = (TTree*)f->Get("mytrigEvent/Events");
   tvertex = (TTree*)f->Get("mypvertex/Events");
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(tvertex);
   tree->AddFriend(telectrons);
   tree->AddFriend(tGenPart);
   tree->AddFriend(tjets);
   tree->AddFriend(ttrigobjs);
   Init(tree);
}

EventLoopAnalysisTemplate::~EventLoopAnalysisTemplate()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EventLoopAnalysisTemplate::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}



Long64_t EventLoopAnalysisTemplate::LoadTree(Long64_t entry)
{
  //cout<<" Set the environment to read one entry"<<endl;
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }

   return centry;
}


void EventLoopAnalysisTemplate::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   triggermap =0;
   PV_x = 0;
   PV_y = 0;
   PV_z = 0;
   Bsp_x = 0;
   Bsp_y = 0;
   Bsp_z = 0;
   electron_pt=0;
   electron_eta=0;
   electron_phi=0;
   electron_dxy=0;
   electron_dz=0;
   electron_isLoose=0;
   electron_isMedium=0;
   electron_isTight=0;
   genelec_pt=0;
   genelec_DRscore=0;
   trk_isHQ = 0;
   //electron_Bsecvec=0;
   //secvec_deltaR=0;
   //secvec_disp=0;
   secvec_posx=0;
   secvec_posy=0;
   secvec_posz=0;
   secvec_px=0;
   secvec_py=0;
   secvec_pz=0;
   secvec_poserrorx=0;
   secvec_poserrory=0;
   secvec_poserrorz=0;
   secvec_phi=0;
   secvec_eta=0;
   secvec_phi1=0;
   secvec_eta1=0;
   secvec_phi2=0;
   secvec_eta2=0;
   secvec_eleTag=0;
   Esecvec_eleTag=0;
   Esecvec_posx=0;
   Esecvec_posy=0;
   Esecvec_posz=0;
   Esecvec_poserrorx=0;
   Esecvec_poserrory=0;
   Esecvec_poserrorz=0;
   Esecvec_phi=0;
   Esecvec_eta=0;
   Esecvec_phi1=0;
   Esecvec_eta1=0;
   Esecvec_phi2=0;
   Esecvec_eta2=0;
   GenPart_pt=0;
   GenPart_eta=0;
   GenPart_phi=0;
   GenPart_px=0;
   GenPart_pdgId=0;
   GenPart_mompdgId=0;
   GenDau_pt=0;
   GenDau_eta=0;
   GenDau_phi=0;
   GenDau_px=0;
   GenDau_pdgId=0;
   GenDau_mompdgId=0;
   GenPart_vx=0;
   GenPart_vy=0;
   GenPart_vz=0;
   jet_pt=0;
   trigobj_e = 0;
   trigobj_pt = 0;
   trigobj_px = 0;
   trigobj_py = 0;
   trigobj_pz = 0;
   trigobj_eta = 0;
   trigobj_phi = 0;


   //b_GenPart_vertex=0;



   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   //Comment out to be able to read map
   //https://root-forum.cern.ch/t/std-map-in-ttree-with-makeclass/14171
   //fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("triggermap",&triggermap,&b_triggermap);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("Bsp_x", &Bsp_x, &b_Bsp_x);
   fChain->SetBranchAddress("Bsp_y", &Bsp_y, &b_Bsp_y);
   fChain->SetBranchAddress("Bsp_z", &Bsp_z, &b_Bsp_z);
   fChain->SetBranchAddress("electron_pt",&electron_pt,&b_electron_pt);
   fChain->SetBranchAddress("electron_eta",&electron_eta,&b_electron_eta);
   fChain->SetBranchAddress("electron_phi",&electron_phi,&b_electron_phi);
   fChain->SetBranchAddress("electron_dxy",&electron_dxy,&b_electron_dxy);
   fChain->SetBranchAddress("electron_dz",&electron_dz,&b_electron_dz);
   fChain->SetBranchAddress("electron_isLoose",&electron_isLoose,&b_electron_isLoose);
   fChain->SetBranchAddress("electron_isMedium",&electron_isMedium,&b_electron_isMedium);
   fChain->SetBranchAddress("electron_isTight",&electron_isTight,&b_electron_isTight);
   fChain->SetBranchAddress("genelec_pt",&genelec_pt,&b_genelec_pt);
   fChain->SetBranchAddress("genelec_DRscore",&genelec_DRscore,&b_genelec_DRscore);
   //fChain->SetBranchAddress("electron_Bsecvec",&electron_Bsecvec,&b_electron_Bsecvec);
   //fChain->SetBranchAddress("secvec_deltaR",&secvec_deltaR,&b_secvec_deltaR);
   //fChain->SetBranchAddress("secvec_disp",&secvec_disp,&b_secvec_disp);
   fChain->SetBranchAddress("secvec_posx",&secvec_posx,&b_secvec_posx);
   fChain->SetBranchAddress("secvec_posy",&secvec_posy,&b_secvec_posy);
   fChain->SetBranchAddress("secvec_posz",&secvec_posz,&b_secvec_posz);
   fChain->SetBranchAddress("secvec_px",&secvec_px,&b_secvec_px);
   fChain->SetBranchAddress("secvec_py",&secvec_py,&b_secvec_py);
   fChain->SetBranchAddress("secvec_pz",&secvec_pz,&b_secvec_pz);
   fChain->SetBranchAddress("secvec_poserrorx",&secvec_poserrorx,&b_secvec_poserrorx);
   fChain->SetBranchAddress("secvec_poserrory",&secvec_poserrory,&b_secvec_poserrory);
   fChain->SetBranchAddress("secvec_poserrorz",&secvec_poserrorz,&b_secvec_poserrorz);
   fChain->SetBranchAddress("secvec_eleTag",&secvec_eleTag,&b_secvec_eleTag);
   fChain->SetBranchAddress("Esecvec_eleTag",&Esecvec_eleTag,&b_Esecvec_eleTag);
   fChain->SetBranchAddress("Esecvec_posx",&Esecvec_posx,&b_Esecvec_posx);
   fChain->SetBranchAddress("Esecvec_posy",&Esecvec_posy,&b_Esecvec_posy);
   fChain->SetBranchAddress("Esecvec_posz",&Esecvec_posz,&b_Esecvec_posz);
   fChain->SetBranchAddress("Esecvec_poserrorx",&Esecvec_poserrorx,&b_Esecvec_poserrorx);
   fChain->SetBranchAddress("Esecvec_poserrory",&Esecvec_poserrory,&b_Esecvec_poserrory);
   fChain->SetBranchAddress("Esecvec_poserrorz",&Esecvec_poserrorz,&b_Esecvec_poserrorz);
   /*fChain->SetBranchAddress("secvec_phi",&secvec_phi,&b_secvec_phi);
   fChain->SetBranchAddress("secvec_eta",&secvec_eta,&b_secvec_eta);
   fChain->SetBranchAddress("secvec_phi1",&secvec_phi1,&b_secvec_phi1);
   fChain->SetBranchAddress("secvec_eta1",&secvec_eta1,&b_secvec_eta1);
   fChain->SetBranchAddress("secvec_phi2",&secvec_phi2,&b_secvec_phi2);
   fChain->SetBranchAddress("secvec_eta2",&secvec_eta2,&b_secvec_eta2);*/
   fChain->SetBranchAddress("GenPart_pt",&GenPart_pt,&b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta",&GenPart_eta,&b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_phi",&GenPart_phi,&b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_px",&GenPart_px,&b_GenPart_px);
   fChain->SetBranchAddress("GenPart_pdgId",&GenPart_pdgId,&b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId",&GenPart_mompdgId,&b_GenPart_mompdgId);
   fChain->SetBranchAddress("GenDau_pt",&GenDau_pt,&b_GenDau_pt);
   fChain->SetBranchAddress("GenDau_eta",&GenDau_eta,&b_GenDau_eta);
   fChain->SetBranchAddress("GenDau_phi",&GenDau_phi,&b_GenDau_phi);
   fChain->SetBranchAddress("GenDau_px",&GenDau_px,&b_GenDau_px);
   fChain->SetBranchAddress("GenDau_pdgId",&GenDau_pdgId,&b_GenDau_pdgId);
   fChain->SetBranchAddress("GenDau_mompdgId",&GenDau_mompdgId,&b_GenDau_mompdgId);
   fChain->SetBranchAddress("GenPart_vx", &GenPart_vx, &b_GenPart_vx);
   fChain->SetBranchAddress("GenPart_vy", &GenPart_vy, &b_GenPart_vy);
   fChain->SetBranchAddress("GenPart_vz", &GenPart_vz, &b_GenPart_vz);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);
   fChain->SetBranchAddress("trigobj_eta",&trigobj_eta,&b_trigobj_eta);
   fChain->SetBranchAddress("trigobj_phi",&trigobj_phi,&b_trigobj_phi);
   fChain->SetBranchAddress("trk_isHQ",&trk_isHQ,&b_trk_isHQ);

   Notify();
}


Bool_t EventLoopAnalysisTemplate::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EventLoopAnalysisTemplate::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

void EventLoopAnalysisTemplate::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t Elecount=0;
  Long64_t Secveccount=0;
  Long64_t SignalCount=0;
  Triggcount=0;



  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%1 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
      cout<<"number of Secvec: "<< secvec_posx->size() << endl;
      cout<<"number of E Secvec: "<< Esecvec_posx->size() << endl;
    }
    //cout<<"flag\n";
    if(jentry==6) {
      //cout<<"flag2\n";
      //Float_t Xpos[secvec_phi->size()];
      //Float_t Ypos[secvec_phi->size()];
      //Float_t W[secvec_phi->size()];
      double Bx,By,Tx,Ty,Bx2,By2,Tx2,Ty2;//DRele;
      for(size_t x=0; x<GenPart_vx->size(); x++){
        if(abs(GenPart_pdgId->at(x))==556){
          Bx=GenPart_vx->at(x)-0.03;
          By=GenPart_vy->at(x)-0.03;
          Tx=GenPart_vx->at(x)+0.03;
          Ty=GenPart_vy->at(x)+0.03;

          Bx2=GenPart_vx->at(x)-0.005;
          By2=GenPart_vy->at(x)-0.005;
          Tx2=GenPart_vx->at(x)+0.005;
          Ty2=GenPart_vy->at(x)+0.005;
        }
      }
      //cout<<"flag\n";
      LW200SecVec_XYGen = new TH2F("LW200SecVec_XYGen","SecVec XY Gen Distribution",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XYSignal1 = new TH2F("LW200SecVec_XYSignal1","SecVec XY Signal Distribution1",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XYSignal2 = new TH2F("LW200SecVec_XYSignal2","SecVec XY Signal Distribution2",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XYSignal3 = new TH2F("LW200SecVec_XYSignal3","SecVec XY Signal Distribution3",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XYSignal4 = new TH2F("LW200SecVec_XYSignal4","SecVec XY Signal Distribution4",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XY = new TH2F("LW200SecVec_XY","SecVec XY Distribution",200,Bx,Tx,200,By,Ty);
      LW200SecVec_XY_P = new TH2F("LW200SecVec_XY_P","SecVec XY Distribution",200,Bx,Tx,200,By,Ty);

      //TGraphErrors* myPlot = new TGraphErrors(secvec_posx->size(),secvec_posx,secvec_posy,secvec_poserrorx,secvec_poserrory);
      for(size_t x=0; x<Esecvec_posx->size(); x++){
        if(Esecvec_eleTag->at(x)!=-1){
          cout<<"secvec eletag "<<Esecvec_eleTag->at(x)<<endl;
          //float modulo=sqrt(Esecvec_px->at(x)*Esecvec_px->at(x)+Esecvec_py->at(x)*Esecvec_py->at(x));


          LW200SecVec_XY->Fill(Esecvec_posx->at(x),Esecvec_posy->at(x),100);

          //LW200SecVec_XY_P->Fill(Esecvec_posx->at(x)+0.01*Esecvec_px->at(x)/modulo,Esecvec_posy->at(x)+0.01*Esecvec_py->at(x)/modulo,50);



        }
      }
      LW200SecVec_XY->Fill(Bsp_x->at(0),Bsp_y->at(0),100);
      LW200SecVec_XY_P->Fill(Bsp_x->at(0),Bsp_y->at(0),100);
      cout<<"Number of electron: "<< electron_pt->size()<<endl;
      //gen secvec impresion
      for(size_t x=0; x<GenPart_vx->size(); x++){
        if(abs(GenPart_pdgId->at(x))==11 && abs(GenPart_mompdgId->at(x))==556){
          //cout<<"SV: "<<GenPart_vx->at(x)<<' '<<GenPart_vy->at(x)<<endl;
          cout<<"SV: "<<GenPart_vx->at(x)<< ' '<<GenPart_vy->at(x)<<endl;
          LW200SecVec_XYGen->Fill(GenPart_vx->at(x),GenPart_vy->at(x),100);
        }
        //primary vertex
        if(abs(GenPart_pdgId->at(x))==556){
          cout<<"PV: "<<GenPart_vx->at(0)<< ' '<<GenPart_vy->at(0)<<endl;
          LW200SecVec_XYGen->Fill(GenPart_vx->at(x),GenPart_vy->at(x),100);
        }
        if(abs(GenPart_pdgId->at(x))==11 && abs(GenPart_mompdgId->at(x))==556){
          for (size_t i = 0; i < electron_pt->size(); i++) {
            cout<<"Ele pt: "<<electron_pt->at(i)<<endl;
            if( genelec_DRscore->at(i)<0.1 && genelec_pt->at(i)==GenPart_pt->at(x) ){
              for(size_t j=0; j<Esecvec_posx->size(); j++){
                //DRele=deltaR(electron_eta->at(i),electron_phi->at(i),secvec_eta->at(j),secvec_phi->at(j));
                //cout<<" Eletag: "<<Esecvec_eleTag->at(j)<<endl;//<<" Elept: "<<genelec_pt->at(Esecvec_eleTag->at(j))<<endl;
                if(Esecvec_eleTag->at(j)==0) {
                  LW200SecVec_XYSignal1->Fill(Esecvec_posx->at(j)-Esecvec_poserrorx->at(j),Esecvec_posy->at(j)-Esecvec_poserrory->at(j),5);
                  //cout<<Esecvec_posx->at(j)<<' '<<Esecvec_posy->at(j)<<endl;
                  //cout<<Esecvec_posx->at(j)-Esecvec_poserrorx->at(j)<<' '<<Esecvec_posy->at(j)-Esecvec_poserrory->at(j)<<"\n\n";
                  LW200SecVec_XYSignal1->Fill(Bsp_x->at(0),Bsp_y->at(0),5);
                  SignalCount++;
                }
                if(Esecvec_eleTag->at(j)==1) {
                  LW200SecVec_XYSignal2->Fill(Esecvec_posx->at(j)-Esecvec_poserrorx->at(j),Esecvec_posy->at(j)-Esecvec_poserrory->at(j),5);
                  //cout<<Esecvec_posx->at(j)<<' '<<Esecvec_posy->at(j)<<endl;
                  //cout<<Esecvec_posx->at(j)-Esecvec_poserrorx->at(j)<<' '<<Esecvec_posy->at(j)-Esecvec_poserrory->at(j)<<"\n\n";
                  LW200SecVec_XYSignal2->Fill(Bsp_x->at(0),Bsp_y->at(0),5);
                  SignalCount++;
                }
                if(Esecvec_eleTag->at(j)==2) {
                  LW200SecVec_XYSignal3->Fill(Esecvec_posx->at(j)-Esecvec_poserrorx->at(j),Esecvec_posy->at(j)-Esecvec_poserrory->at(j),5);
                  //cout<<Esecvec_posx->at(j)<<' '<<Esecvec_posy->at(j)<<endl;
                  //cout<<Esecvec_posx->at(j)-Esecvec_poserrorx->at(j)<<' '<<Esecvec_posy->at(j)-Esecvec_poserrory->at(j)<<"\n\n";
                  LW200SecVec_XYSignal3->Fill(Bsp_x->at(0),Bsp_y->at(0),5);
                  SignalCount++;
                }
                if(Esecvec_eleTag->at(j)==i) {
                  LW200SecVec_XYSignal4->Fill(Esecvec_posx->at(j)-Esecvec_poserrorx->at(j),Esecvec_posy->at(j)-Esecvec_poserrory->at(j),10);
                  //cout<<Esecvec_posx->at(j)<<' '<<Esecvec_posy->at(j)<<endl;
                  //cout<<Esecvec_posx->at(j)-Esecvec_poserrorx->at(j)<<' '<<Esecvec_posy->at(j)-Esecvec_poserrory->at(j)<<"\n\n";
                  LW200SecVec_XYSignal4->Fill(Bsp_x->at(0),Bsp_y->at(0),10);
                  SignalCount++;
                }
              }
            }
          }
        }
      }
      //LW200SecVec_XY->FillN(secvec_phi->size(),Xpos,Ypos,W,1);


      TFile* XYfile = new TFile("XYSecVec.root","RECREATE");
      LW200SecVec_XYGen->Write();
      LW200SecVec_XYSignal1->Write();
      LW200SecVec_XYSignal2->Write();
      LW200SecVec_XYSignal3->Write();
      LW200SecVec_XYSignal4->Write();
      LW200SecVec_XY->Write();
      LW200SecVec_XY_P->Write();
      XYfile->Close();

    }
    //cout<<"flag2\n";
    if(electron_pt->size()==0)Elecount++;//cout<<"Load the current event "<<jentry<<" 0 ele"<<'\n';
    if(electron_pt->size()==1)Elecount++;//cout<<"Load the current event "<<jentry<<" 1 ele"<<'\n';
    Long64_t ientry = LoadTree(jentry);
    //cout<<ientry<<endl;
    //cout<<"flag3\n";
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    //cout<<"flag4\n";

    analysis();
    //cout<<"flag5\n";
    Secveccount+=Esecvec_posx->size();
  }
  cout<<"Number Ele "<<Elecount<<endl;
  cout<<"Triggcount "<<Triggcount<<endl;
  cout<<"Secvec count "<<Secveccount<<endl;
  cout<<"Signal count "<<SignalCount<<endl;


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;

  //minimal selection including trigger requirement
  //if (!MinimalSelection()) return;
  //counter_ms++;


  //Secvec secvecstudy
  /*float dx,dy,dz,SVdR,SVdR1,SVdR2,dist,maxx,maxy,maxz;
  size_t SVCount=0;
  for(size_t x=0; x<secvec_posx->size(); x++){
    for(size_t y=x+1; y<secvec_posx->size(); y++){
      dx=abs(secvec_posx->at(x)-secvec_posx->at(y));
      dy=abs(secvec_posy->at(x)-secvec_posy->at(y));
      dz=abs(secvec_posz->at(x)-secvec_posz->at(y));
      dist=sqrt(dx*dx+dy*dy+dz*dz);
      //deta=abs(secvec_eta->at(x)-secvec_eta->at(y));
      //cout<<deta<<endl;
      //hists[0]->Fill(dx+dy+dz);
      if(dist<0.2){
        SVdR=deltaR(secvec_eta->at(x),secvec_phi->at(x),secvec_eta->at(y),secvec_phi->at(y));
        SVdR1=deltaR(secvec_eta1->at(x),secvec_phi1->at(x),secvec_eta1->at(y),secvec_phi1->at(y));
        SVdR2=deltaR(secvec_eta2->at(x),secvec_phi2->at(x),secvec_eta2->at(y),secvec_phi2->at(y));
        if(SVdR==0){
          maxx=max(secvec_poserrorx->at(x),secvec_poserrorx->at(y));
          maxy=max(secvec_poserrory->at(x),secvec_poserrory->at(y));
          maxz=max(secvec_poserrorz->at(x),secvec_poserrorz->at(y));
          if(dx<maxx && dy<maxy && dz<maxz){
            hists[0]->Fill(1);
            hists[1]->Fill(dist);
            if(maxx>0.02) hists[3]->Fill(0.020);
            else hists[3]->Fill(maxx);
            if(maxy>0.02) hists[4]->Fill(0.020);
            else hists[4]->Fill(maxy);
            if(maxz>0.02) hists[5]->Fill(0.020);
            else hists[5]->Fill(maxz);
            SVCount++;
            hists[6]->Fill(SVdR);
            hists[7]->Fill(SVdR1);
            hists[8]->Fill(SVdR2);
          }
          else hists[0]->Fill(0);
        }
        else hists[0]->Fill(0);
      }
      else hists[0]->Fill(0);
    }
  }
  hists[2]->Fill(SVCount);*/

  //checking electrons HQ.
  /*for(size_t x=0; x<electron_pt->size(); x++){
    for(size_t y=0; y<GenPart_pt->size(); y++){
      if(abs(GenPart_pdgId->at(y))==11 && abs(GenPart_mompdgId->at(y))==556){
        if(genelec_DRscore->at(x)<0.1 && genelec_pt->at(x)==GenPart_pt->at(y)){
          hists[9]->Fill(trk_isHQ->at(x));
          if(trk_isHQ->at(x)==1){
            hists[10]->Fill(electron_pt->at(x));
            //hists[11]->Fill(trk_pt->at(x));
          }

        }
      }
    }
  }*/

//Filling Electrons pt
  //if(electron_pt->size()!=electron_Bsecvec->size())cout<<"aqui\n";
  //if(secvec_posx->size()==0)cout<<"aqui\n"<<electron_pt->size()<<endl;
  /*if(genelec_pt->size()!=electron_pt->size())cout<<genelec_pt->size()<<' '<<electron_pt->size()<<endl;
  if(electron_pt->size()!=0){
    for (size_t i = 0; i < electron_pt->size(); i++) {
      if (electron_pt->at(i)>Minpt) {
        //hists[1]->Fill(electron_pt->at(i));
        hists[2]->Fill(electron_eta->at(i));
      }

      if(electron_Bsecvec->at(i)!=-1){
        if(secvec_disp->size()>electron_Bsecvec->at(i)) {
          //if(!electron_isLoose->at(i))hists[12]->Fill(secvec_disp->at(electron_Bsecvec->at(i)));
          //if(electron_isLoose->at(i)) hists[11]->Fill(secvec_disp->at(electron_Bsecvec->at(i)));
        }
      }
      //compare to MC
      //if(GenPart_mompdgId->size()!=GenPart_pt->size())cout<<GenPart_mompdgId->size()<<' '<<GenPart_pt->size();
      for (size_t j = 0; j < GenPart_pt->size(); j++) {
        if(abs(GenPart_pdgId->at(j)) == 11 && abs(GenPart_mompdgId->at(j)) == 556){
          if( genelec_DRscore->at(i)<0.1 && genelec_pt->at(i)==GenPart_pt->at(j) ){
            hists[1]->Fill(electron_pt->at(i));
            LW200electron_dxy->Fill(electron_dxy->at(i));

            if(abs(electron_dxy->at(i))<0.02){
              LW200SGenele_dxy->Fill(electron_dxy->at(i));
              hists[4]->Fill(electron_pt->at(i));
              //////TrigObj////////////////
              float saveDR=100;
              //bool saveQ=false;
              for (size_t y=0; y<trigobj_px->size(); y++){
                float DRet=deltaR(electron_eta->at(i),electron_phi->at(i),trigobj_eta->at(y),trigobj_phi->at(y));
                if(DRet<saveDR){
                   saveDR=DRet;
                   //saveQ=trk_isHQ;
                }
              }

              LW200TrigObjDR->Fill(saveDR);

              if (saveDR<0.2) LW200TrigObj->Fill(1);
              else LW200TrigObj->Fill(0);
            }

            //////////Best Secondary vertex/////////////////////
            if(electron_Bsecvec->at(i)!=-1){
              if(secvec_disp->size()>electron_Bsecvec->at(i)) hists[12]->Fill(secvec_disp->at(electron_Bsecvec->at(i)));
            }
          }
        }
      }
    }
  }
  //Filling Genpart pt
  int genelec=0;
  int nsgenelec=0;
  //cout<<GenPart_mompdgId->size()<<' '<<GenPart_pt->size() <<'\n';
  for (size_t i = 0; i < GenDau_pt->size(); i++) {
    if (abs(GenDau_mompdgId->at(i)) == 556) {
      //cout <<GenDau_mompdgId->at(i)<<' '<< GenDau_pdgId->at(i) << '\n';
      if( abs(GenDau_pdgId->at(i)) == 11 && GenDau_pt->at(i)>Minpt){
        if(GenDau_pt->at(i)<Minpt)genelec++;
        //hists[4]->Fill(GenDau_pt->at(i));
        hists[5]->Fill(GenDau_eta->at (i));
      }
    }
    if (abs(GenDau_mompdgId->at(i)) == 23) {
      hists[6]->Fill(GenDau_pt->at(i));
      hists[7]->Fill(GenDau_eta->at (i));
    }
  }
  ///Ver si hay vertices secundarios
  Double_t pvx=0;
  Double_t pvy=0;
  Double_t pvz=0;
  //if(GenPart_pt->size()!=GenPart_vx->size())cout<<GenPart_pt->size()<<' '<<GenPart_vx->size()<<endl;

  for (size_t j = 0; j < GenPart_pt->size(); j++) {
    if( abs(GenPart_pdgId->at(j)) == 556 ){
      pvx = GenPart_vx->at(j);
      pvy = GenPart_vy->at(j);
      pvz = GenPart_vz->at(j);
    }
  }
  int cj=0;
  for (size_t i = 0; i < GenPart_pt->size(); i++) {
    if (abs(GenPart_mompdgId->at(i)) == 556) {
      if( abs(GenPart_pdgId->at(i)) == 23) {
        Double_t dx=GenPart_vx->at(i)-pvx;
        Double_t dy=GenPart_vy->at(i)-pvy;
        Double_t dz=GenPart_vz->at(i)-pvz;
        Double_t disp = sqrtf( dx*dx + dy*dy + dz*dz );
        if (disp!=INFINITY) {
          hists[11]->Fill(disp);
          cj++;
          //cout<<disp<<endl;
        }
      }
    }
  }
  if(cj!=2)cout<<cj<<endl;


  for (size_t i = 0; i < GenPart_pt->size(); i++) {
    if( abs(GenPart_pdgId->at(i)) == 11 && GenPart_pt->at(i)>Minpt ){
      nsgenelec++;
      hists[9]->Fill(GenPart_pt->at(i));
      hists[10]->Fill(GenPart_eta->at (i));
    }
  }
  hists[3]->Fill(genelec);
  hists[8]->Fill(nsgenelec);

  ////filtered Data ////
  int GoodEleCount=0;
  if(electron_pt->size() == 0){
    //cout<<"Aqui\n";
    LW200Genelec_disp_f->Fill(-1);
    LW200EleBsecvec_f->Fill(-1);
  }
  else{
    //cout<<"Aqui no\n";
    for (size_t i = 0; i < electron_pt->size(); i++) {
      if(electron_pt->at(i)>15){
        GoodEleCount++;
      }
    }
    if(GoodEleCount>=2){
      for (size_t j = 0; j < GenPart_pt->size(); j++) {
        if( abs(GenPart_pdgId->at(j)) == 556 ){
          pvx = GenPart_vx->at(j);
          pvy = GenPart_vy->at(j);
          pvz = GenPart_vz->at(j);
        }
      }
      for (size_t j = 0; j < GenPart_pt->size(); j++) {
        if (abs(GenPart_mompdgId->at(j)) == 556 && abs(GenPart_pdgId->at(j)) == 23) {
          Double_t dx=GenPart_vx->at(j)-pvx;
          Double_t dy=GenPart_vy->at(j)-pvy;
          Double_t dz=GenPart_vz->at(j)-pvz;
          Double_t disp = sqrtf( dx*dx + dy*dy + dz*dz );
          if (disp!=INFINITY) {
            LW200Genelec_disp_f->Fill(disp);
          }
        }
      }
      for (size_t i = 0; i < electron_pt->size(); i++) {
        //compare to MC
        //if(GenPart_mompdgId->size()!=GenPart_pt->size())cout<<GenPart_mompdgId->size()<<' '<<GenPart_pt->size();
        for (size_t j = 0; j < GenPart_pt->size(); j++) {
          if(abs(GenPart_pdgId->at(j)) == 11 && abs(GenPart_mompdgId->at(j)) == 556){
            if( genelec_DRscore->at(i)<0.1 && genelec_pt->at(i)==GenPart_pt->at(j) ){
              if(electron_Bsecvec->at(i)!=-1){
                if(secvec_disp->size()>electron_Bsecvec->at(i)) LW200EleBsecvec_f->Fill(secvec_disp->at(electron_Bsecvec->at(i)));
              }
            }
          }
        }
      }

    }
  }

  /////////TrigObj Ele fit///////////////////////
  //vector<bool> TobjisFound;
  //tobj.clear()
  for (size_t y=0; y<trigobj_px->size(); y++){
    float saveDR=100;
    //bool saveQ=false;
    for (size_t x=0; x<electron_pt->size(); x++){
      float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
      if(DRet<saveDR){
         saveDR=DRet;
         //saveQ=trk_isHQ;
      }
    }

    LW200TrigObjDR->Fill(saveDR);

    if (saveDR<0.2) LW200TrigObj->Fill(1);
    else LW200TrigObj->Fill(0);
  }*/


}//------analysis()

///////////////deltaR
float EventLoopAnalysisTemplate::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deta = eta1 - eta2;
  float dphi = std::abs(phi1 - phi2);
  if (dphi > 3.14159)
    dphi -= (2 * 3.14159);
  return sqrt(deta * deta + dphi * dphi);
}


/*
 * Perform a selection on the minimal requirements of an event
 */
//-----------------------------------------------------------------
Float_t EventLoopAnalysisTemplate::MinimalSelection(Int_t entry)
{
//-----------------------------------------------------------------

 //cout<<"Applying minimal selection"<<endl;
  Float_t isTrigger = 0;

  //Check trigger and acceptance bit
  for (map<string, int>::iterator it=triggermap->begin();it!=triggermap->end();it++){
    //for (size_t i = 0; i < 6; i++) {

      if(it->first.find(triggerRequest[entry])!=string::npos){
        isTrigger = it->second;
        //if(isTrigger!=1)cout<<it->first<<"  "<<it->second<<endl;
      }
    //}

  }


  return isTrigger;

}//------MinimalSelection




//-----------------------------------------------------------------
int main()
{
//-----------------------------------------------------------------

  gROOT->ProcessLine("#include<map>");

  /*
 * Compute event weights to be used for the respective datasets
 *
 * The event weight reweights the full dataset so that the sum of the weights
 * is equal to the expected number of events in data. The expectation is given by
 * multiplying the integrated luminosity of the data with the cross-section of
 * the process in the datasets divided by the number of simulated events.
 */
  //const float integratedLuminosity = 4.412 * 1000.0; // Run2012B only
  //const float integratedLuminosity = 7.055 * 1000.0; // Run2012C only


  map<string, pair<string,float> > sampleNames;
  sampleNames.insert(make_pair("myoutput_200",make_pair("LW200",1)));




  //loop over sample files with names  defined above
  for(map< string,pair<string,float> >::iterator it=sampleNames.begin();
      it!=sampleNames.end();it++){

    TString samplename = it->first;
    TString thelabel = it->second.first;
    Float_t sampleweight = it->second.second;

    TStopwatch time;
    time.Start();
    cout << ">>> Processing sample " << samplename <<" with label "<<thelabel<<" and weight "<<sampleweight<<":" <<endl;


    TString filename = samplesBasePath+samplename+".root";

    cout<<"Build the analysis object with file "<<filename<<endl;
    EventLoopAnalysisTemplate mytemplate(filename,thelabel,sampleweight);

    cout<<"Run the event loop"<<endl;
    mytemplate.Loop();
    time.Stop();
    time.Print();
  }

  TFile* hfile = new TFile("MergeAnalysis.root","RECREATE");

  //Save signal region histos
  /*LW200electron_num->Write();
  LW200electron_pt->Write();
  LW200electron_dxy->Write();
  LW200electron_eta->Write();
  LW200SGenele_num->Write();
  LW200SGenele_pt->Write();
  LW200SGenele_dxy->Write();
  LW200SGenele_eta->Write();
  LW200GenZdau_pt->Write();
  LW200GenZdau_eta->Write();
  LW200Genelec_num->Write();
  LW200Genelec_pt->Write();
  LW200Genelec_eta->Write();
  LW200Genelec_disp->Write();
  LW200EleBsecvec->Write();
  LW200Genelec_disp_f->Write();
  LW200EleBsecvec_f->Write();
  LW200TrigObj->Write();
  LW200TrigObjDR->Write();*/
  LW200SecVec_pos->Write();
  LW200SecVec_dist->Write();
  LW200SecVec_errorx->Write();
  LW200SecVec_errory->Write();
  LW200SecVec_errorz->Write();
  LW200SecVec_num->Write();
  LW200SecVec_dR->Write();
  LW200SecVec_dR1->Write();
  LW200SecVec_dR2->Write();
  LW200SecVec_TrkHQ->Write();
  LW200SecVec_HQElept->Write();
  LW200SecVec_HQTrkpt->Write();
  //LW200SecVec_XY->Write();

  hfile->Close();


  return 0;

}
