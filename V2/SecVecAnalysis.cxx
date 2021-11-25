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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o SecVecAnalysis SecVecAnalysis.cxx $(root-config --cflags --libs)
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
#include <bits/stdc++.h>

using namespace std;


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
TH1F* LW200electron_num = new TH1F("LW200electron_num","number of events with elec/phot pt>20GeV",10,0,10);
TH1F* LW200electron_pt = new TH1F("LW200electron_pt","Electrons pt for missing trigg",100,0,200);
TH1F* LW200electron_eta = new TH1F("LW200electron_eta","Electrons eta for missing trigg",100,-5,5);
TH1F* LW200SGenele_num = new TH1F("LW200SGenele_num","Number of signal gen-electrons per event (pt<15GeV)",3,0,3);
TH1F* LW200SGenele_pt = new TH1F("LW200SGenele_pt","Signal Genele pt ",100,0,200);
TH1F* LW200SGenele_eta = new TH1F("LW200SGenele_eta","Signal Genele eta",100,-5,5);
TH1F* LW200Genelec_num = new TH1F("LW200Genelec_num","number of gen-electrons",50,0,100);
TH1F* LW200Genelec_pt = new TH1F("LW200Genelec_pt","Genelec pt",100,0,200);
TH1F* LW200Genelec_eta = new TH1F("LW200Genelec_eta","Genelec eta",100,-5,5);
TH1F* LW200GenZdau_pt = new TH1F("LW200GenZdau_pt","GensZdau pt for missing trigg",100,0,200);
TH1F* LW200GenZdau_eta = new TH1F("LW200GenZdau_eta","GensZdau eta for missing trigg",100,-5,5);
TH1F* LW200EleBsecvec = new TH1F("Electron best match","Best matched secondary vertex displacement",100,0,0.1);

const std::string samplesBasePath = "";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 17;
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
  TTree          *tphotons;
  TTree          *tGenPart;
  TTree          *tTrack;


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
  vector<float>   *electron_pt;
  vector<float>   *electron_eta;
  vector<float>   *electron_phi;
  vector<float>   *electron_Bsecvec;
  vector<float>   *secvec_deltaR;
  vector<float>   *secvec_disp;
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

  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_electron_pt;
  TBranch        *b_electron_eta;
  TBranch        *b_electron_phi;
  TBranch        *b_electron_Bsecvec;
  TBranch        *b_secvec_deltaR;
  TBranch        *b_secvec_disp;
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


  EventLoopAnalysisTemplate(TString filename, TString labeltag, Float_t theweight);
  virtual ~EventLoopAnalysisTemplate();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  void analysis();
  Float_t MinimalSelection(Int_t entry);

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;

  hists[0]=LW200electron_num;
  hists[1]=LW200electron_pt;
  hists[2]=LW200electron_eta;
  hists[3]=LW200SGenele_num;
  hists[4]=LW200SGenele_pt;
  hists[5]=LW200SGenele_eta;
  hists[6]=LW200GenZdau_pt;
  hists[7]=LW200GenZdau_eta;
  hists[8]=LW200Genelec_num;
  hists[9]=LW200Genelec_pt;
  hists[10]=LW200Genelec_eta;
  hists[12]=LW200EleBsecvec;

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
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(telectrons);
   tree->AddFriend(tGenPart);
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
   electron_pt=0;
   electron_eta=0;
   electron_phi=0;
   electron_Bsecvec=0;
   secvec_deltaR=0;
   secvec_disp=0;
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
   fChain->SetBranchAddress("electron_pt",&electron_pt,&b_electron_pt);
   fChain->SetBranchAddress("electron_eta",&electron_eta,&b_electron_eta);
   fChain->SetBranchAddress("electron_phi",&electron_phi,&b_electron_phi);
   fChain->SetBranchAddress("electron_Bsecvec",&electron_Bsecvec,&b_electron_Bsecvec);
   fChain->SetBranchAddress("secvec_deltaR",&secvec_deltaR,&b_secvec_deltaR);
   fChain->SetBranchAddress("secvec_disp",&secvec_disp,&b_secvec_disp);
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
  Triggcount=0;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%10000 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
    }
    if(electron_pt->size()==0)Elecount++;//cout<<"Load the current event "<<jentry<<" 0 ele"<<'\n';
    if(electron_pt->size()==1)Elecount++;//cout<<"Load the current event "<<jentry<<" 1 ele"<<'\n';
    Long64_t ientry = LoadTree(jentry);
    //cout<<ientry<<endl;
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    analysis();

  }
  cout<<"Number Ele "<<Elecount<<endl;
  cout<<"Triggcount "<<Triggcount<<endl;


}


//-----------------------------------------------------------------
void EventLoopAnalysisTemplate::analysis()
{
//-----------------------------------------------------------------

  //cout<<"analysis() execution"<<endl;

  //minimal selection including trigger requirement
  //if (!MinimalSelection()) return;
  //counter_ms++;


  //fill histograms for signal region
  //Int_t histsize = sizeof(hists)/sizeof(hists[0]);
  //Float_t pstmp;
//Filling Electrons pt
  //if(electron_pt->size()!=electron_Bsecvec->size())cout<<"aqui\n";
  if(electron_pt->size()!=0){
    for (size_t i = 0; i < electron_pt->size(); i++) {
      if (electron_pt->at(i)>Minpt) {
        hists[1]->Fill(electron_pt->at(i));
        hists[2]->Fill(electron_eta->at(i));
      }
      //if(electron_Bsecvec->at(i)>secvec_disp->size())cout<<"aqui\n";
      if(electron_Bsecvec->at(i)!=-1){
        hists[12]->Fill(secvec_disp->at(electron_Bsecvec->at(i)-1));
        /*cout<<'\n'<<electron_Bsecvec->at(i)<<' '<<secvec_disp->size()<<'\n';
        cout<<electron_pt->at(i)<<' '<<secvec_disp->at(electron_Bsecvec->at(i)-1)<<endl;*/
      }
      else hists[12]->Fill(-1);
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
        hists[4]->Fill(GenDau_pt->at(i));
        hists[5]->Fill(GenDau_eta->at (i));
      }
    }
    if (abs(GenDau_mompdgId->at(i)) == 23) {
      hists[6]->Fill(GenDau_pt->at(i));
      hists[7]->Fill(GenDau_eta->at (i));
    }
  }
  ///Ver si hay vertices secundarios
  for (size_t i = 0; i < GenDau_pt->size(); i++) {
    if (GenDau_mompdgId->at(i) == 556) {
      if( abs(GenDau_pdgId->at(i)) == 11){
        for (size_t j = 0; j < GenPart_pt->size(); j++) {
          if( GenPart_pdgId->at(j) == 556 ){
            //cout<<GenDau_px->at(i)-GenPart_px->at(j)<<endl;
          }
        }
      }
    }
  }


  for (size_t i = 0; i < GenPart_pt->size(); i++) {
    if( abs(GenPart_pdgId->at(i)) == 11 && GenPart_pt->at(i)>Minpt ){
      nsgenelec++;
      hists[9]->Fill(GenPart_pt->at(i));
      hists[10]->Fill(GenPart_eta->at (i));
    }
  }
  hists[3]->Fill(genelec);
  hists[8]->Fill(nsgenelec);
}//------analysis()

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
  sampleNames.insert(make_pair("LWSM200DnR",make_pair("LW200",1)));




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

  TFile* hfile = new TFile("SecVecAnalysis.root","RECREATE");

  //Save signal region histos
  LW200electron_num->Write();
  LW200electron_pt->Write();
  LW200electron_eta->Write();
  LW200SGenele_num->Write();
  LW200SGenele_pt->Write();
  LW200SGenele_eta->Write();
  LW200GenZdau_pt->Write();
  LW200GenZdau_eta->Write();
  LW200Genelec_num->Write();
  LW200Genelec_pt->Write();
  LW200Genelec_eta->Write();
  LW200EleBsecvec->Write();

  hfile->Close();


  return 0;

}
