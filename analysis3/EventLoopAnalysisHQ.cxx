//////////////////////////////////////////////////////////////////////
// This template analysis code has been built with fragments from the
// classes automatically obtained by the TTree MakeClass() method.
//
// The template shows the structre of a potential analysis code
// where more TTree friends can be added with more physics objects.
//
// The analysis part is based on the RDataFrame analysis example by Stefan Wunch:
// https://github.com/cms-opendata-analyses/HiggsTauTauNanoAODOutreachAnalysis
//
// Done with ROOT version 5.32/00
// from TTree Events/Events
// found on file: myoutput.root
//
//
// Compile me with:
// g++ -std=c++11 -g -O3 -Wall -Wextra -o EventLoopAnalysisHQ EventLoopAnalysisHQ.cxx $(root-config --cflags --libs)
/////////////////////////////////////////////////////////////////////

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
//Include C++ classes
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

using namespace std;


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
const std::string samplesBasePath = "Datos/";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 60;

//Histograms for signal region
TH1F* dataRunB_npv = new TH1F("dataRunB_npv","Number of primary vertices",25,5,30);

TH1F* dataRunC_npv  = new TH1F("dataRunC_npv","Number of primary vertices",25,5,30);

TH1F* ZLL_npv = new TH1F("ZLL_npv","Number of primary vertices",25,5,30);

TH1F* TT_npv = new TH1F("TT_npv","Number of primary vertices",25,5,30);

TH1F* W3J_npv = new TH1F("W3J_npv","Number of primary vertices",25,5,30);

TH1F* W2J_npv = new TH1F("W2J_npv","Number of primary vertices",25,5,30);

TH1F* W1J_npv = new TH1F("W1J_npv","Number of primary vertices",25,5,30);

TH1F* ttZ_npv = new TH1F("ttZ_npv","Number of primary vertices",25,5,30);

TH1F* WW_npv = new TH1F("WW_npv","Number of primary vertices",25,5,30);

TH1F* WZ_npv = new TH1F("WZ_npv","Number of primary vertices",25,5,30);

TH1F* LW200_npv = new TH1F("LW200_npv","Number of primary vertices",25,5,30);

TH1F* LW300_npv = new TH1F("LW300_npv","Number of primary vertices",25,5,30);

//TH1F* LW400_npv = new TH1F("LW400_npv","Number of primary vertices",25,5,30);

//TH1F* LW500_npv = new TH1F("LW500_npv","Number of primary vertices",25,5,30);

TH1F* dataRunB_nsv = new TH1F("dataRunB_nsv","Number of secondary vertices",20,0,2000);

TH1F* dataRunC_nsv  = new TH1F("dataRunC_nsv","Number of secondary vertices",20,0,2000);

TH1F* ZLL_nsv = new TH1F("ZLL_nsv","Number of secondary vertices",20,0,2000);

TH1F* TT_nsv = new TH1F("TT_nsv","Number of secondary vertices",20,0,2000);

TH1F* W3J_nsv = new TH1F("W3J_nsv","Number of secondary vertices",20,0,2000);

TH1F* W2J_nsv = new TH1F("W2J_nsv","Number of secondary vertices",20,0,2000);

TH1F* W1J_nsv = new TH1F("W1J_nsv","Number of secondary vertices",20,0,2000);

TH1F* ttZ_nsv = new TH1F("ttZ_nsv","Number of secondary vertices",20,0,2000);

TH1F* WW_nsv = new TH1F("WW_nsv","Number of secondary vertices",20,0,2000);

TH1F* WZ_nsv = new TH1F("WZ_nsv","Number of secondary vertices",20,0,2000);

TH1F* LW200_nsv = new TH1F("LW200_nsv","Number of secondary vertices",20,0,2000);

TH1F* LW300_nsv = new TH1F("LW300_nsv","Number of secondary vertices",20,0,2000);

//TH1F* LW400_nsv = new TH1F("LW400_nsv","Number of secondary vertices",20,0,2000);

//TH1F* LW500_nsv = new TH1F("LW500_nsv","Number of secondary vertices",20,0,2000);

TH1F* dataRunB_svd = new TH1F("dataRunB_svd","secondary vertex displacement",100,0,1);

TH1F* dataRunC_svd  = new TH1F("dataRunC_svd","secondary vertex displacement",100,0,1);

TH1F* ZLL_svd = new TH1F("ZLL_svd","secondary vertex displacement",100,0,1);

TH1F* TT_svd = new TH1F("TT_svd","secondary vertex displacement",100,0,1);

TH1F* W3J_svd = new TH1F("W3J_svd","secondary vertex displacement",100,0,1);

TH1F* W2J_svd = new TH1F("W2J_svd","secondary vertex displacement",100,0,1);

TH1F* W1J_svd = new TH1F("W1J_svd","secondary vertex displacement",100,0,1);

TH1F* ttZ_svd = new TH1F("ttZ_svd","secondary vertex displacement",100,0,1);

TH1F* WW_svd = new TH1F("WW_svd","secondary vertex displacement",100,0,1);

TH1F* WZ_svd = new TH1F("WZ_svd","secondary vertex displacement",100,0,1);

TH1F* LW200_svd = new TH1F("LW200_svd","secondary vertex displacement",100,0,1);

TH1F* LW300_svd = new TH1F("LW300_svd","secondary vertex displacement",100,0,1);

//TH1F* LW400_svd = new TH1F("LW400_svd","secondary vertex displacement",100,0,1);

//TH1F* LW500_svd = new TH1F("LW500_svd","secondary vertex displacement",100,0,1);

TH1F* dataRunB_JetMass = new TH1F("dataRunB_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* dataRunC_JetMass  = new TH1F("dataRunC_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* ZLL_JetMass = new TH1F("ZLL_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* TT_JetMass = new TH1F("TT_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W3J_JetMass = new TH1F("W3J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W2J_JetMass = new TH1F("W2J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* W1J_JetMass = new TH1F("W1J_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* ttZ_JetMass = new TH1F("ttZ_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* WW_JetMass = new TH1F("WW_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* WZ_JetMass = new TH1F("WZ_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* LW200_JetMass = new TH1F("LW200_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* LW300_JetMass = new TH1F("LW300_JetMass","Invariant mass from DiJets",800,0,400);

//TH1F* LW400_JetMass = new TH1F("LW400_JetMass","Invariant mass from DiJets",800,0,400);

//TH1F* LW500_JetMass = new TH1F("LW500_JetMass","Invariant mass from DiJets",800,0,400);

TH1F* dataRunB_LWMass = new TH1F("dataRunB_LWMass","Invariant mass from LW",800,0,400);

TH1F* dataRunC_LWMass  = new TH1F("dataRunC_LWMass","Invariant mass from LW",800,0,400);

TH1F* ZLL_LWMass = new TH1F("ZLL_LWMass","Invariant mass from LW",800,0,400);

TH1F* TT_LWMass = new TH1F("TT_LWMass","Invariant mass from LW",800,0,400);

TH1F* W3J_LWMass = new TH1F("W3J_LWMass","Invariant mass from LW",800,0,400);

TH1F* W2J_LWMass = new TH1F("W2J_LWMass","Invariant mass from LW",800,0,400);

TH1F* W1J_LWMass = new TH1F("W1J_LWMass","Invariant mass from LW",800,0,400);

TH1F* ttZ_LWMass = new TH1F("ttZ_LWMass","Invariant mass from LW",800,0,400);

TH1F* WW_LWMass = new TH1F("WW_LWMass","Invariant mass from LW",800,0,400);

TH1F* WZ_LWMass = new TH1F("WZ_LWMass","Invariant mass from LW",800,0,400);

TH1F* LW200_LWMass = new TH1F("LW200_LWMass","Invariant mass from LW",800,0,400);

TH1F* LW300_LWMass = new TH1F("LW300_LWMass","Invariant mass from LW",800,0,400);

//TH1F* LW400_LWMass = new TH1F("LW400_LWMass","Invariant mass from LW",800,0,400);

//TH1F* LW500_LWMass = new TH1F("LW500_LWMass","Invariant mass from LW",800,0,400);

//TH1F* LW200_JetHQ = new TH1F("LW200_JetHQ","JetHQ",2,0,2);

//Requiered trigger
//string triggerRequest = "HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50";
string triggerRequest[] = {"HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
                           "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_R9Id85_Photon22_R9Id85"};

// Fixed size dimensions of array or collections stored in the TTree if any.


class EventLoopAnalysisTemplate {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *tevents;
  TTree          *tvertex;
  TTree          *ttrigger;
  TTree           *tmuons;
  TTree           *ttaus;
  TTree           *tmets;
  TTree           *tjets;
  TTree           *telectrons;
  TTree           *ttrigobjs;

  Int_t           fCurrent; //!current Tree number in a TChain
  TString          labeltag;
  TString         filename;
  Float_t          theweight;

  //array to keep histograms to be written and easily loop over them
  TH1F            *hists[nhists];

  // Declaration of example leaf types
  Int_t           run;
  UInt_t          luminosityBlock;
  ULong64_t	   event;
  Int_t           PV_npvs;
  Int_t           numbersecvec;
  std::map<std::string, int> *triggermap;
  vector<float>   *PV_x;
  vector<float>   *PV_y;
  vector<float>   *PV_z;
  vector<float>   *muon_pt;
  vector<float>   *muon_eta;
  vector<float>   *muon_phi;
  vector<float>   *muon_ch;
  vector<float>   *muon_tightid;
  vector<float>   *muon_pfreliso03all;
  vector<float>   *muon_mass;
  vector<float>   *tau_pt;
  vector<float>   *tau_eta;
  vector<float>   *tau_phi;
  vector<float>   *tau_ch;
  vector<float>   *tau_iddecaymode;
  vector<float>   *tau_idisotight;
  vector<float>   *tau_idantieletight;
  vector<float>   *tau_idantimutight;
  vector<float>   *tau_reliso_all;
  vector<float>   *tau_mass;
  vector<float>   *jet_mass;
  vector<float>   *jet_e;
  vector<float>   *jet_pt;
  vector<float>   *corr_jet_pt;
  vector<float>   *jet_pz;
  vector<float>   *jet_px;
  vector<float>   *jet_py;
  vector<float>   *jet_phi;
  vector<float>   *jet_eta;
  vector<float>   *NConstituents;
  vector<float>   *NeutralHF;
  vector<float>   *NeutralEMF;
  vector<float>   *MuonF;
  vector<float>   *ChargedEMF;
  vector<float>   *ChargedHF;
  vector<float>   *ChargedMult;
  vector<float>   *electron_e;
  vector<float>   *electron_pt;
  vector<float>   *electron_pz;
  vector<float>   *electron_px;
  vector<float>   *electron_py;
  vector<float>   *electron_phi;
  vector<float>   *electron_eta;
  vector<float>   *trk_isHQ;
  vector<float>   *trigobj_e;
  vector<float>   *trigobj_pt;
  vector<float>   *trigobj_pz;
  vector<float>   *trigobj_px;
  vector<float>   *trigobj_py;
  vector<float>   *trigobj_phi;
  vector<float>   *trigobj_eta;
  vector<float>   *secvec_posx;
  vector<float>   *secvec_posy;
  vector<float>   *secvec_posz;
  Float_t         met_pt;
  Float_t         met_phi;

  // List of example branches
  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_PV_npvs;   //!
  TBranch        *b_numbersecvec;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_PV_x;   //!
  TBranch        *b_PV_y;   //!
  TBranch        *b_PV_z;   //!
  TBranch        *b_muon_pt;   //!
  TBranch        *b_muon_eta;   //!
  TBranch        *b_muon_phi;   //!
  TBranch        *b_muon_ch;   //!
  TBranch        *b_muon_tightid;   //!
  TBranch        *b_muon_pfreliso03all;   //!
  TBranch        *b_muon_mass;   //!
  TBranch        *b_tau_pt;   //!
  TBranch        *b_tau_eta;   //!
  TBranch        *b_tau_phi;   //!
  TBranch        *b_tau_ch;   //!
  TBranch        *b_tau_iddecaymode;   //!
  TBranch        *b_tau_idisotight;   //!
  TBranch        *b_tau_idantieletight;   //!
  TBranch        *b_tau_idantimutight;   //!
  TBranch        *b_tau_reliso_all;   //!
  TBranch        *b_tau_mass;   //!
  TBranch        *b_met_pt;   //!
  TBranch        *b_met_phi;   //!
  TBranch        *b_jet_mass;
  TBranch        *b_jet_e;
  TBranch        *b_jet_pt;
  TBranch        *b_corr_jet_pt;
  TBranch        *b_jet_pz;
  TBranch        *b_jet_px;
  TBranch        *b_jet_py;
  TBranch        *b_jet_phi;
  TBranch        *b_jet_eta;
  TBranch        *b_NConstituents;
  TBranch        *b_NeutralHF;
  TBranch        *b_NeutralEMF;
  TBranch        *b_MuonF;
  TBranch        *b_ChargedEMF;
  TBranch        *b_ChargedHF;
  TBranch        *b_ChargedMult;
  TBranch        *b_electron_e;
  TBranch        *b_electron_pt;
  TBranch        *b_electron_pz;
  TBranch        *b_electron_px;
  TBranch        *b_electron_py;
  TBranch        *b_electron_phi;
  TBranch        *b_electron_eta;
  TBranch        *b_trk_isHQ;
  TBranch        *b_trigobj_e;
  TBranch        *b_trigobj_pt;
  TBranch        *b_trigobj_pz;
  TBranch        *b_trigobj_px;
  TBranch        *b_trigobj_py;
  TBranch        *b_trigobj_phi;
  TBranch        *b_trigobj_eta;
  TBranch        *b_secvec_posx;
  TBranch        *b_secvec_posy;
  TBranch        *b_secvec_posz;

  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual float    deltaR(float eta1, float phi1, float eta2, float phi2);
  //virtual void     Show(string filtter);
  void analysis();
  bool MinimalSelection();

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;


  //Load histograms for signal region
  hists[0] = dataRunB_npv;
  hists[1] = dataRunC_npv;
  hists[2] = ZLL_npv;
  hists[3] = TT_npv;
  hists[4] = W3J_npv;
  hists[5] = W2J_npv;
  hists[6] = W1J_npv;
  hists[21] = LW200_npv;
  hists[7] = dataRunB_JetMass;
  hists[8] = dataRunC_JetMass;
  hists[9] = ZLL_JetMass;
  hists[10] = TT_JetMass;
  hists[11] = W3J_JetMass;
  hists[12] = W2J_JetMass;
  hists[13] = W1J_JetMass;
  hists[22] = LW200_JetMass;
  hists[14] = dataRunB_LWMass;
  hists[15] = dataRunC_LWMass;
  hists[16] = ZLL_LWMass;
  hists[17] = TT_LWMass;
  hists[18] = W3J_LWMass;
  hists[19] = W2J_LWMass;
  hists[20] = W1J_LWMass;
  hists[23] = LW200_LWMass;
  hists[24] = WW_npv;
  hists[25] = WZ_npv;
  hists[26] = ttZ_npv;
  hists[27] = WW_JetMass;
  hists[28] = WZ_JetMass;
  hists[29] = ttZ_JetMass;
  hists[30] = WW_LWMass;
  hists[31] = WZ_LWMass;
  hists[32] = ttZ_LWMass;
  hists[33] = LW300_LWMass;
  //hists[34] = LW400_LWMass;
  //hists[35] = LW500_LWMass;
  hists[34] = LW300_JetMass;
  //hists[37] = LW400_JetMass;
  //hists[38] = LW500_JetMass;
  hists[35] = LW300_npv;
  //hists[40] = LW400_npv;
  //hists[41] = LW500_npv;
  hists[36] = dataRunB_nsv;
  hists[37] = dataRunC_nsv;
  hists[38] = ZLL_nsv;
  hists[39] = TT_nsv;
  hists[40] = W3J_nsv;
  hists[41] = W2J_nsv;
  hists[42] = W1J_nsv;
  hists[43] = WW_nsv;
  hists[44] = WZ_nsv;
  hists[45] = ttZ_nsv;
  hists[46] = LW200_nsv;
  hists[47] = LW200_nsv;
  //hists[40] = LW400_nsv;
  //hists[41] = LW500_nsv;
  hists[48] = dataRunB_svd;
  hists[49] = dataRunC_svd;
  hists[50] = ZLL_svd;
  hists[51] = TT_svd;
  hists[52] = W3J_svd;
  hists[53] = W2J_svd;
  hists[54] = W1J_svd;
  hists[55] = WW_svd;
  hists[56] = WZ_svd;
  hists[57] = ttZ_svd;
  hists[58] = LW200_svd;
  hists[59] = LW200_svd;
  //hists[40] = LW400_svd;
  //hists[41] = LW500_svd;


// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree* tree = 0;
   TFile *f = TFile::Open(filename);
   //trigger should go first as it is the more complicated one
   tree = (TTree*)f->Get("mytriggers/Events");
   //Get trees for friendship
   tevents = (TTree*)f->Get("myevents/Events");
   tvertex = (TTree*)f->Get("mypvertex/Events");
   tmuons = (TTree*)f->Get("mymuons/Events");
   ttaus = (TTree*)f->Get("mytaus/Events");
   tmets = (TTree*)f->Get("mymets/Events");
   tjets = (TTree*)f->Get("myjets/Events");
   telectrons = (TTree*)f->Get("myelectrons/Events");
   ttrigobjs = (TTree*)f->Get("mytrigEvent/Events");
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(tvertex);
   tree->AddFriend(tmuons);
   tree->AddFriend(ttaus);
   tree->AddFriend(tmets);
   tree->AddFriend(tjets);
   tree->AddFriend(telectrons);
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
   muon_pt = 0;
   muon_eta = 0;
   muon_phi = 0;
   muon_ch = 0;
   muon_tightid = 0;
   muon_pfreliso03all = 0;
   muon_mass = 0;
   tau_pt = 0;
   tau_eta = 0;
   tau_phi = 0;
   tau_ch = 0;
   tau_iddecaymode = 0;
   tau_idisotight = 0;
   tau_idantieletight = 0;
   tau_idantimutight = 0;
   tau_reliso_all = 0;
   tau_mass = 0;
   jet_e = 0;
   jet_pt = 0;
   corr_jet_pt = 0;
   jet_px = 0;
   jet_py = 0;
   jet_pz = 0;
   jet_phi = 0;
   jet_eta = 0;
   NConstituents = 0;
   NeutralHF = 0;
   NeutralEMF = 0;
   MuonF = 0;
   ChargedEMF = 0;
   ChargedHF = 0;
   ChargedMult = 0;
   electron_e = 0;
   electron_pt = 0;
   electron_px = 0;
   electron_py = 0;
   electron_pz = 0;
   electron_phi = 0;
   electron_eta = 0;
   trk_isHQ = 0;
   trigobj_e = 0;
   trigobj_pt = 0;
   trigobj_px = 0;
   trigobj_py = 0;
   trigobj_pz = 0;
   trigobj_phi = 0;
   trigobj_eta = 0;
   secvec_posx = 0;
   secvec_posy = 0;
   secvec_posz = 0;

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
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("numbersecvec", &numbersecvec, &b_numbersecvec);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("triggermap",&triggermap,&b_triggermap);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("corr_jet_pt",&corr_jet_pt,&b_corr_jet_pt);
   fChain->SetBranchAddress("jet_pt",&jet_pt,&b_jet_pt);
   fChain->SetBranchAddress("jet_px",&jet_px,&b_jet_px);
   fChain->SetBranchAddress("jet_py",&jet_py,&b_jet_py);
   fChain->SetBranchAddress("jet_pz",&jet_pz,&b_jet_pz);
   fChain->SetBranchAddress("jet_phi",&jet_phi,&b_jet_phi);
   fChain->SetBranchAddress("jet_eta",&jet_eta,&b_jet_eta);
   fChain->SetBranchAddress("jet_e",&jet_e,&b_jet_e);
   fChain->SetBranchAddress("NConstituents",&NConstituents,&b_NConstituents);
   fChain->SetBranchAddress("NeutralHF",&NeutralHF,&b_NeutralHF);
   fChain->SetBranchAddress("NeutralEMF",&NeutralEMF,&b_NeutralEMF);
   fChain->SetBranchAddress("MuonF",&MuonF,&b_MuonF);
   fChain->SetBranchAddress("ChargedEMF",&ChargedEMF,&b_ChargedEMF);
   fChain->SetBranchAddress("ChargedHF",&ChargedHF,&b_ChargedHF);
   fChain->SetBranchAddress("ChargedMult",&ChargedMult,&b_ChargedMult);
   fChain->SetBranchAddress("electron_px",&electron_px,&b_electron_px);
   fChain->SetBranchAddress("electron_py",&electron_py,&b_electron_py);
   fChain->SetBranchAddress("electron_pz",&electron_pz,&b_electron_pz);
   fChain->SetBranchAddress("electron_phi",&electron_phi,&b_electron_phi);
   fChain->SetBranchAddress("electron_eta",&electron_eta,&b_electron_eta);
   fChain->SetBranchAddress("electron_e",&electron_e,&b_electron_e);
   fChain->SetBranchAddress("trk_isHQ",&trk_isHQ,&b_trk_isHQ);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_phi",&trigobj_phi,&b_trigobj_phi);
   fChain->SetBranchAddress("trigobj_eta",&trigobj_eta,&b_trigobj_eta);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);
   fChain->SetBranchAddress("secvec_posx",&secvec_posx,&b_secvec_posx);
   fChain->SetBranchAddress("secvec_posy",&secvec_posy,&b_secvec_posy);
   fChain->SetBranchAddress("secvec_posz",&secvec_posz,&b_secvec_posz);

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

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%100000 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
    }
    //cout<<"Load the current event"<<endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    analysis();

  }


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;

  //minimal selection including trigger requirement
  if (!MinimalSelection()) return;
  //counter_ms++;

  //////////JetSelection///////
  vector<bool> JetisHQ;
  JetisHQ.clear();
  size_t Jhqcount=0;
  for(size_t x=0; x<jet_e->size(); x++){
    if(abs(jet_eta->at(x))<2.5){
      if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8){
        JetisHQ.push_back(true);
        Jhqcount++;
      }
      else JetisHQ.push_back(false);
    }
    else{
      if(NConstituents->at(x)>1 && NeutralHF->at(x)<0.9 && MuonF->at(x)<0.8 &&
          ChargedHF->at(x)>0 && ChargedEMF->at(x)>0 && ChargedMult->at(x)<0.80){
            JetisHQ.push_back(true);
            Jhqcount++;
          }
      else JetisHQ.push_back(false);
    }
  }
  if(Jhqcount<4) return;
  /////Identify electron as Trig OBJ
  vector<bool> TobjisFound;
  vector<int>  TobjisHQ;
  TobjisFound.clear();
  TobjisHQ.clear();
  size_t objcount=0;
  size_t hqcount=0;
  for (size_t y=0; y<trigobj_e->size(); y++){
    float saveDR=100;
    int saveQ=0;
    for (size_t x=0; x<electron_e->size(); x++){
      float DRet=deltaR(electron_eta->at(x),electron_phi->at(x),trigobj_eta->at(y),trigobj_phi->at(y));
      if(DRet<saveDR){
         saveDR=DRet;
         saveQ=trk_isHQ->at(x);
      }
    }
    if (saveDR<0.1){
      TobjisFound.push_back(true);
      TobjisHQ.push_back(saveQ);
      objcount++;
      if(saveQ==1) hqcount++;
    }
    else {
      TobjisFound.push_back(false);
      TobjisHQ.push_back(saveQ);
    }
  }
  if(objcount<2) return;
  if(hqcount<2) return;
  //fill histograms for signal region
  Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  for (Int_t j=0;j<histsize;++j){
    TString histname = TString(hists[j]->GetName());
    TString thelabel = histname(0,histname.First("_"));
    TString thevar = histname(histname.First("_")+1,histname.Sizeof());

    if (thelabel == labeltag){

      //primary vertices
      if(thevar == "npv"){
	       hists[j]->Fill(PV_npvs,theweight);
      }

      //secondary Vertices
      if(thevar == "nsv"){
	       hists[j]->Fill(numbersecvec,theweight);
      }

      //secondary vertex displacements
      if(thevar == "svd"){
        float dx,dy,dz,disp;
        for (size_t i = 0; i < secvec_posx->size(); i++) {
          dx=PV_x->at(0)-secvec_posx->at(i);
          dy=PV_y->at(0)-secvec_posy->at(i);
          dz=PV_z->at(0)-secvec_posz->at(i);
          disp=sqrt( dx*dx + dy*dy + dz*dz );
          hists[j]->Fill(disp,theweight);
        }
      }

      //JetMass
      if(thevar == "JetMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        if(JetisHQ.size()!=jet_e->size())cout<<"size error\n";
        for(size_t i=0; i < jet_e->size(); i++){
          //LW200_JetHQ->Fill(JetisHQ.at(i));
          for(size_t k=0; k < jet_e->size(); k++){
            px=0,py=0,pz=0,e=0,m=0;
            if(i!=k && JetisHQ.at(i) && JetisHQ.at(k)){
              px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(k))*corr_jet_pt->at(k);
              py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(k))*corr_jet_pt->at(k);
              float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
              float corr2=corr_jet_pt->at(k)/jet_pt->at(k);
              pz=jet_pz->at(i)*corr1+jet_pz->at(k)*corr2;
              e=jet_e->at(i)*corr1+jet_e->at(k)*corr2;
              m=sqrt( e*e - px*px - py*py - pz*pz );

              hists[j]->Fill(m,theweight);
            }
           }
        }
      }
      if(thevar == "LWMass"){
        ////////Jet Inv Mass ///////////////////
        float px,py,pz,e,m;
        //correctedJetMass
        //float corr_pt;
        for(size_t i=0; i < jet_e->size(); i++){
          for(size_t k=0; k < jet_e->size(); k++){
            for(size_t l=0; l < trigobj_e->size(); l++){
              px=0,py=0,pz=0,e=0,m=0;
              if(i!=k && JetisHQ.at(i) && JetisHQ.at(k)){
                if(TobjisFound.at(l) && TobjisHQ.at(l)){
                  px=cos(jet_phi->at(i))*corr_jet_pt->at(i) + cos(jet_phi->at(k))*corr_jet_pt->at(k) + trigobj_px->at(l);
                  py=sin(jet_phi->at(i))*corr_jet_pt->at(i) + sin(jet_phi->at(k))*corr_jet_pt->at(k) + trigobj_py->at(l);
                  float corr1=corr_jet_pt->at(i)/jet_pt->at(i);
                  float corr2=corr_jet_pt->at(k)/jet_pt->at(k);
                  pz=jet_pz->at(i)*corr1+jet_pz->at(k)*corr2+trigobj_pz->at(l);
                  e=jet_e->at(i)*corr1+jet_e->at(k)*corr2+trigobj_e->at(l);
                  m=sqrt( e*e - px*px - py*py - pz*pz );

                  hists[j]->Fill(m,theweight);
                }
              }
            }
          }
        }
      }
    }
  }




}//------analysis()

/*
 * Perform a selection on the minimal requirements of an event
 */
//-----------------------------------------------------------------
bool EventLoopAnalysisTemplate::MinimalSelection()
{
//-----------------------------------------------------------------

 //cout<<"Applying minimal selection"<<endl;
  bool isTrigger = false;

  //Check trigger and acceptance bit
  for(size_t x=0; x<4; x++){
    for (map<string, int>::iterator it=triggermap->begin();it!=triggermap->end();it++){
      if(it->first.find(triggerRequest[x])!=string::npos &&
         it->second!=0){
  	 //cout<<it->first<<"  "<<it->second<<endl;
        isTrigger = true;
      }
    }
  }

  return isTrigger;

}//------MinimalSelection

//deltaR
float EventLoopAnalysisTemplate::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deta = eta1 - eta2;
  float dphi = std::abs(phi1 - phi2);
  if (dphi > 3.14159)
    dphi -= (2 * 3.14159);
  return deta * deta + dphi * dphi;
}

//Hist
//void EventLoopAnalysisTemplate::Hist()

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
  const float integratedLuminosity = 11.467 * 1000.0; // Run2012B+C

  const float W1J_w =  6381.2 / 29784800.0 * integratedLuminosity;
  const float W2J_w =  2039.8 / 30693853.0 * integratedLuminosity;
  const float W3J_w =  612.5 / 15241144.0 * integratedLuminosity;
  const float TT_w = 225.2 / 6423106.0 * integratedLuminosity;
  const float ZLL_w = 3503.7 / 30458871.0 * integratedLuminosity;
  const float LW200_w = 0.0059 / 150000 * integratedLuminosity;
  const float LW300_w = 0.00096 / 150000 * integratedLuminosity;
  //const float LW400_w = 0.00023 / 150000 * integratedLuminosity;
  //const float LW500_w = 0.00006 / 150000 * integratedLuminosity;
  const float WW_w = 5.824 / 1933120 * integratedLuminosity;
  const float WZ_w = 2.207 / 3215990 * integratedLuminosity;
  const float ttZ_w = 0.175 / 787495 * integratedLuminosity;
  const float dataRunB_w = 1.0;
  const float dataRunC_w = 1.0;


  map<string, pair<string,float> > sampleNames;
  sampleNames.insert(make_pair("WWJetsTo2L2Nu",make_pair("WW",WW_w)));
  sampleNames.insert(make_pair("WZJetsTo2L2Q",make_pair("WZ",WZ_w)));
  sampleNames.insert(make_pair("ttbarZ",make_pair("ttZ",ttZ_w)));
  sampleNames.insert(make_pair("W1JetsToLNu",make_pair("W1J",W1J_w)));
  sampleNames.insert(make_pair("W2JetsToLNu",make_pair("W2J",W2J_w)));
  sampleNames.insert(make_pair("W3JetsToLNu",make_pair("W3J",W3J_w)));
  sampleNames.insert(make_pair("TTbar",make_pair("TT",TT_w)));
  sampleNames.insert(make_pair("DYJetsToLL",make_pair("ZLL",ZLL_w)));
  sampleNames.insert(make_pair("LWSM200DnR",make_pair("LW200",LW200_w)));
  sampleNames.insert(make_pair("LWSM300DnR",make_pair("LW300",LW300_w)));
  //sampleNames.insert(make_pair("LWSM400DnR",make_pair("LW400",LW400_w)));
  //sampleNames.insert(make_pair("LWSM500DnR",make_pair("LW500",LW500_w)));
  sampleNames.insert(make_pair("Run2012B_DoublePhoton",make_pair("dataRunB",dataRunB_w)));
  sampleNames.insert(make_pair("Run2012C_DoublePhoton",make_pair("dataRunC",dataRunC_w)));




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

  TFile* hfile = new TFile("HQ/histogramsHQ.root","RECREATE");

  //Save signal region histos
  dataRunB_npv->Write();
  dataRunC_npv->Write();
  ZLL_npv->Write();
  TT_npv->Write();
  W3J_npv->Write();
  W2J_npv->Write();
  W1J_npv->Write();
  WW_npv->Write();
  WZ_npv->Write();
  ttZ_npv->Write();
  LW200_npv->Write();
  LW300_npv->Write();
  //LW400_npv->Write();
  //LW500_npv->Write();
  dataRunB_JetMass->Write();
  dataRunC_JetMass->Write();
  ZLL_JetMass->Write();
  TT_JetMass->Write();
  W3J_JetMass->Write();
  W2J_JetMass->Write();
  W1J_JetMass->Write();
  WW_JetMass->Write();
  WZ_JetMass->Write();
  ttZ_JetMass->Write();
  LW200_JetMass->Write();
  LW300_JetMass->Write();
  //LW400_JetMass->Write();
  //LW500_JetMass->Write();
  dataRunB_LWMass->Write();
  dataRunC_LWMass->Write();
  ZLL_LWMass->Write();
  TT_LWMass->Write();
  W3J_LWMass->Write();
  W2J_LWMass->Write();
  W1J_LWMass->Write();
  WW_LWMass->Write();
  WZ_LWMass->Write();
  ttZ_LWMass->Write();
  LW200_LWMass->Write();
  LW300_LWMass->Write();
  //LW400_LWMass->Write();
  //LW500_LWMass->Write();
  //LW200_JetHQ->Write();
  dataRunB_nsv->Write();
  dataRunC_nsv->Write();
  ZLL_nsv->Write();
  TT_nsv->Write();
  W3J_nsv->Write();
  W2J_nsv->Write();
  W1J_nsv->Write();
  WW_nsv->Write();
  WZ_nsv->Write();
  ttZ_nsv->Write();
  LW200_nsv->Write();
  LW300_nsv->Write();
  //LW400_nsv->Write();
  //LW500_nsv->Write();
  dataRunB_svd->Write();
  dataRunC_svd->Write();
  ZLL_svd->Write();
  TT_svd->Write();
  W3J_svd->Write();
  W2J_svd->Write();
  W1J_svd->Write();
  WW_svd->Write();
  WZ_svd->Write();
  ttZ_svd->Write();
  LW200_svd->Write();
  LW300_svd->Write();
  //LW400_svd->Write();
  //LW500_svd->Write();

  hfile->Close();


  return 0;

}
