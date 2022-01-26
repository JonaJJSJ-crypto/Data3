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
// g++ -std=c++11 -g -O3 -Wall -Wextra -o LW200TriggerAnalysis TriggerAnalysis.cxx $(root-config --cflags --libs)
/////////////////////////////////////////////////////////////////////

//Include ROOT classes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TLatex.h"
#include "TStopwatch.h"
//Include C++ classes
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <tuple>

using namespace std;


/*
 * Base path to local filesystem or to EOS containing the datasets
 */
//const std::string samplesBasePath = "root://eospublic.cern.ch//eos/opendata/cms/upload/od-workshop/ws2021/";
TH1F* LW200triggps_1 = new TH1F("LWtrigg1","HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50",2,0,2);
TH1F* LW200triggps_2 = new TH1F("LWtrigg2","HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",2,0,2);
TH1F* LW200triggps_3 = new TH1F("LWtrigg3","HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",2,0,2);
TH1F* LW200triggps_4 = new TH1F("LWtrigg4","HLT_Photon36_R9Id85_Photon22_R9Id85",2,0,2);
TH1F* LW200triggps_5 = new TH1F("LWtrigg5","HLT_Photon36_Photon22",2,0,2);
TH1F* LW200triggps_6 = new TH1F("LWtrigg6","HLT_Photon26_Photon18",2,0,2);
TH1F* LW200electron_num = new TH1F("LW200electron_num","number of electrons for missing trigg",10,0,10);
TH1F* LW200electron_pt = new TH1F("LW200electron_pt","Electrons pt for missing trigg",100,0,200);
TH1F* LW200electron_eta = new TH1F("LW200electron_eta","Electrons eta for missing trigg",100,-3,3);
TH1F* LW200photon_num = new TH1F("LW200photon_num","number of photons for missing trigg",10,0,10);
TH1F* LW200photon_pt = new TH1F("LW200photon_pt","photons pt for missing trigg",100,0,200);
TH1F* LW200photon_eta = new TH1F("LW200photon_eta","photons eta for missing trigg",100,-3,3);
TH1F* LW200PassTrigg = new TH1F("LW200PassTrigg","Booleano trigger passed Event",2,0,2);
TH1F* LW200ele = new TH1F("LW200PassTrigg","Booleano trigger passed Event",2,0,2);

const std::string samplesBasePath = "";


//book example histograms for specific variables
//copy them in the constructor if you add more
const int nhists = 12;

//Histograms for signal region


//Requiered trigger
string triggerRequest[] = {"HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85",
                           "HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50",
                           "HLT_Photon36_R9Id85_Photon22_R9Id85"};

// Fixed size dimensions of array or collections stored in the TTree if any.


class EventLoopAnalysisTemplate {
public :

  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *tevents;
  TTree          *ttrigger;
  TTree          *telectrons;
  TTree          *tphotons;
  TTree          *ttrigobjs;
  TTree          *tGenPart;


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
  vector<float>   *electron_iso;
  vector<float>   *trk_isHQ;
  vector<float>   *photon_pt;
  vector<float>   *photon_eta;
  vector<float>   *photon_phi;
  vector<float>   *trigobj_e;
  vector<float>   *trigobj_pt;
  vector<float>   *trigobj_pz;
  vector<float>   *trigobj_px;
  vector<float>   *trigobj_py;
  vector<float>   *trigobj_eta;
  vector<float>   *trigobj_phi;
  vector<float>   *GenPart_pt;
  vector<float>   *GenPart_eta;
  vector<float>   *GenPart_phi;
  vector<float>   *GenPart_px;
  vector<float>   *GenPart_pdgId;
  vector<float>   *GenPart_mompdgId;
  vector<float>   *genelec_pt;
  vector<float>   *genelec_DRscore;

  TBranch        *b_run;   //!
  TBranch        *b_luminosityBlock;   //!
  TBranch        *b_event;   //!
  TBranch        *b_triggermap;   //!
  TBranch        *b_electron_pt;
  TBranch        *b_electron_eta;
  TBranch        *b_electron_phi;
  TBranch        *b_electron_iso;
  TBranch        *b_trk_isHQ;
  TBranch        *b_photon_pt;
  TBranch        *b_photon_eta;
  TBranch        *b_photon_phi;
  TBranch        *b_trigobj_e;
  TBranch        *b_trigobj_pt;
  TBranch        *b_trigobj_pz;
  TBranch        *b_trigobj_px;
  TBranch        *b_trigobj_py;
  TBranch        *b_trigobj_eta;
  TBranch        *b_trigobj_phi;
  TBranch        *b_GenPart_pt;
  TBranch        *b_GenPart_eta;
  TBranch        *b_GenPart_phi;
  TBranch        *b_GenPart_px;
  TBranch        *b_GenPart_pdgId;
  TBranch        *b_GenPart_mompdgId;
  TBranch        *b_genelec_pt;
  TBranch        *b_genelec_DRscore;


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
  bool MinimalSelection();

};



EventLoopAnalysisTemplate::EventLoopAnalysisTemplate(TString thefile, TString thelabel, Float_t sampleweight) : fChain(0)
{
  //Prepare some info for the object:
  filename = thefile;
  labeltag = thelabel;
  theweight = sampleweight;

  hists[0]=LW200triggps_1;
  hists[1]=LW200triggps_2;
  hists[2]=LW200triggps_3;
  hists[3]=LW200triggps_4;
  hists[4]=LW200triggps_5;
  hists[5]=LW200triggps_6;
  hists[6]=LW200electron_num;
  hists[7]=LW200electron_pt;
  hists[8]=LW200electron_eta;
  hists[9]=LW200photon_num;
  hists[10]=LW200photon_pt;
  hists[11]=LW200photon_eta;

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree* tree = 0;
   TFile *f = TFile::Open(filename);
   //trigger should go first as it is the more complicated one
   tree = (TTree*)f->Get("mytriggers/Events");
   //Get trees for friendship
   tevents = (TTree*)f->Get("myevents/Events");
   telectrons = (TTree*)f->Get("myelectrons/Events");
   tphotons = (TTree*)f->Get("myphotons/Events");
   ttrigobjs = (TTree*)f->Get("mytrigEvent/Events");
   tGenPart = (TTree*)f->Get("mygenparticle/Events");
   //Make friends so we can have access to friends variables
   //we may not use all of the available information
   //it is just an example
   tree->AddFriend(tevents);
   tree->AddFriend(telectrons);
   tree->AddFriend(tphotons);
   tree->AddFriend(ttrigobjs);
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
   electron_iso=0;
   trk_isHQ=0;
   photon_pt=0;
   photon_eta=0;
   photon_phi=0;
   trigobj_e = 0;
   trigobj_pt = 0;
   trigobj_px = 0;
   trigobj_py = 0;
   trigobj_pz = 0;
   trigobj_eta = 0;
   trigobj_phi = 0;
   GenPart_pt=0;
   GenPart_eta=0;
   GenPart_phi=0;
   GenPart_px=0;
   GenPart_pdgId=0;
   GenPart_mompdgId=0;
   genelec_pt=0;
   genelec_DRscore=0;

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
   fChain->SetBranchAddress("electron_iso",&electron_iso,&b_electron_iso);
   fChain->SetBranchAddress("trk_isHQ",&trk_isHQ,&b_trk_isHQ);
   fChain->SetBranchAddress("photon_pt",&photon_pt,&b_photon_pt);
   fChain->SetBranchAddress("photon_eta",&photon_eta,&b_photon_eta);
   fChain->SetBranchAddress("photon_phi",&photon_phi,&b_photon_phi);
   fChain->SetBranchAddress("trigobj_pt",&trigobj_pt,&b_trigobj_pt);
   fChain->SetBranchAddress("trigobj_px",&trigobj_px,&b_trigobj_px);
   fChain->SetBranchAddress("trigobj_py",&trigobj_py,&b_trigobj_py);
   fChain->SetBranchAddress("trigobj_pz",&trigobj_pz,&b_trigobj_pz);
   fChain->SetBranchAddress("trigobj_phi",&trigobj_phi,&b_trigobj_phi);
   fChain->SetBranchAddress("trigobj_eta",&trigobj_eta,&b_trigobj_eta);
   fChain->SetBranchAddress("trigobj_e",&trigobj_e,&b_trigobj_e);
   fChain->SetBranchAddress("GenPart_pt",&GenPart_pt,&b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta",&GenPart_eta,&b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_phi",&GenPart_phi,&b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_px",&GenPart_px,&b_GenPart_px);
   fChain->SetBranchAddress("GenPart_pdgId",&GenPart_pdgId,&b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId",&GenPart_mompdgId,&b_GenPart_mompdgId);
   fChain->SetBranchAddress("genelec_pt",&genelec_pt,&b_genelec_pt);
   fChain->SetBranchAddress("genelec_DRscore",&genelec_DRscore,&b_genelec_DRscore);

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

  Long64_t EventCount=0;
  Long64_t EventDiscount=0;

  Long64_t SignalCount=0;
  Long64_t SignalDiscount=0;

  Triggcount=0;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Just an informative printout
    if(jentry%100000 == 0) {
      cout<<"Processed "<<jentry<<" events out of "<<nentries<<endl;
    }
    if(electron_pt->size()==0)Elecount++;//cout<<"Load the current event "<<jentry<<" 0 ele"<<'\n';
    if(electron_pt->size()==1)Elecount++;//cout<<"Load the current event "<<jentry<<" 1 ele"<<'\n';



    //if(electron_pt->size()!=electron_iso->size() || electron_pt->size()!=trk_isHQ->size()) cout <<electron_pt->size()<<' '<<electron_iso->size()<<' '<<trk_isHQ->size()<<endl;
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
  bool pstmp;
  pstmp=MinimalSelection();
  vector<float> ElePtTemp;


  if(electron_pt->size()>0){
    for (size_t x = 0; x < electron_pt->size(); x++) {ElePtTemp.push_back(electron_pt->at(x));}
    sort(ElePtTemp.begin(),ElePtTemp.end());
    if (ElePtTemp.back()>40) LW200PassTrigg->Fill(pstmp);
  }

  for (Int_t j=0;j<6;++j){

    TString histname = TString(hists[j]->GetName());
    TString thelabel = histname(0,histname.First("_"));
    TString thevar = histname(7);
    //cout<<thevar<<'\n';
    pstmp=MinimalSelection();
    hists[j]->Fill(pstmp);
    vector<float> GenPtTemp;
    GenPtTemp.clear();
    for(size_t x=0; x<GenPart_pt->size(); x++){if(abs(GenPart_pdgId->at(x))==11) GenPtTemp.push_back(GenPart_pt->at(x));}//save vector tmp
    sort(GenPtTemp.begin(), GenPtTemp.end());//sort vector temp
    if(GenPtTemp.size()>1){
      for(size_t x=0; x<GenPart_pt->size(); x++){
        if( GenPtTemp.back() == GenPart_pt->at(x) && abs(GenPart_pdgId->at(x))==11 ){
          for (size_t i = 0; i < electron_pt->size(); i++) {
            if( genelec_DRscore->at(i)<0.1 && genelec_pt->at(i)==GenPart_pt->at(x) ){
              if(GenPart_pt->at(x)/electron_pt->at(i)<1) LW20040GenEle->AddPoint(GenPart_pt->at(x),pstmp*GenPart_pt->at(x)/electron_pt->at(i));
              else LW20040GenEle->AddPoint( GenPart_pt->at(x),pstmp*electron_pt->at(i)/GenPart_pt->at(x) );
            }
          }
        }
      }
    }


    ///Tobj
    vector<float> ElePtTemp;
    vector<float> ToPtTemp;
    if(electron_pt->size()>1 && trigobj_pt->size()>1){
      for (size_t x = 0; x < electron_pt->size(); x++) {ElePtTemp.push_back(electron_pt->at(x));}
      sort(ElePtTemp.begin(),ElePtTemp.end());
      LW200Mele_pt->Fill(ElePtTemp.back());
      LW200Sele_pt->Fill(ElePtTemp.end()[-2]);
      for(size_t y=0; y<trigobj_pt->size(); y++){ToPtTemp.push_back(trigobj_pt->at(y));}
      sort(ToPtTemp.begin(),ToPtTemp.end());
      LW200MTobj_pt->Fill(ToPtTemp.back());
      LW200STobj_pt->Fill(ToPtTemp.end()[-2]);
      if (ElePtTemp.back()>40) LW200PassTrigg->Fill(pstmp);
      for (size_t x = 0; x < electron_pt->size(); x++) {
        if( electron_pt->at(x)==ElePtTemp.back() ){
          float saveEleDR=100;
          float TrigObjpt=0;
          for(size_t y=0; y<trigobj_pt->size(); y++){
            if(saveEleDR > deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y))) {
              saveEleDR= deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y) );

              TrigObjpt= trigobj_pt->at(y);
            }
            //cout<<"TrigObj: "<<deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y) )<<endl;
          }
          LW200MTobj_ele_dR->Fill(saveEleDR);
          //cout<<"SaveDR: "<<saveEleDR<<endl;
          if( saveEleDR<0.1){
            //cout<<" valid ele \n";
            if(electron_pt->at(x)/TrigObjpt<1) LW20040Ele->AddPoint(electron_pt->at(x),pstmp*electron_pt->at(x)/TrigObjpt);
            else LW20040Ele->AddPoint(electron_pt->at(x),pstmp*TrigObjpt/electron_pt->at(x));
          }
        }
        if( electron_pt->at(x)==ElePtTemp.end()[-2] ){
          float saveEleDR=100;
          float TrigObjpt=0;
          for(size_t y=0; y<trigobj_pt->size(); y++){
            if(saveEleDR > deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y))) {
              saveEleDR= deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y) );

              TrigObjpt= trigobj_pt->at(y);
            }
            //cout<<"TrigObj: "<<deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y) )<<endl;
          }
          LW200STobj_ele_dR->Fill(saveEleDR);
        }
      }
    }

    if(pstmp==0 && j==1){
      Triggcount++;
      hists[6]->Fill(electron_pt->size());
      for (size_t i = 0; i < electron_pt->size(); i++) {
              //cout<<electron_pt->at(i)<<'\n';
              hists[7]->Fill(electron_pt->at(i));
              hists[8]->Fill(electron_eta->at(i));
      }
      hists[9]->Fill(photon_pt->size());
      for (size_t i = 0; i < photon_pt->size(); i++) {
              hists[10]->Fill(photon_pt->at(i));
              hists[11]->Fill(photon_eta->at(i));
      }


    }
  }
  ////////////////////////TObj/////////////////////////////
  vector<float> GenPtTemp;
  GenPtTemp.clear();
  for(size_t x=0; x<GenPart_pt->size(); x++){if(abs(GenPart_pdgId->at(x))==11) GenPtTemp.push_back(GenPart_pt->at(x));}

  if(trigobj_pt->size()>1){
    for(size_t y=0; y<trigobj_pt->size(); y++){
      float saveTODR=100;
      float savePT=0;

      for (size_t x = 0; x < electron_pt->size(); x++) {
        float tmpDR=deltaR(electron_eta->at(x), electron_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y));
        if(saveTODR> tmpDR){
          saveTODR=tmpDR;
          savePT=electron_pt->at(x);
        }
      }
      if(saveTODR<0.1){
        if(savePT/trigobj_pt->at(y)<1)LW200TO_ele_ptr->AddPoint(trigobj_pt->at(y),savePT/trigobj_pt->at(y));
        else LW200TO_ele_ptr->AddPoint(trigobj_pt->at(y),trigobj_pt->at(y)/savePT);
      }
      saveTODR=100;
      savePT=0;
      for(size_t x=0;x < photon_pt->size(); x++){
        float tmpDR=deltaR(photon_eta->at(x), photon_phi->at(x), trigobj_eta->at(y), trigobj_phi->at(y));
        if(saveTODR> tmpDR){
          saveTODR=tmpDR;
          savePT=photon_pt->at(x);
        }
      }
      if(saveTODR<0.1){
        if(savePT/trigobj_pt->at(y)<1)LW200TO_phot_ptr->AddPoint(trigobj_pt->at(y),savePT/trigobj_pt->at(y));
        else LW200TO_phot_ptr->AddPoint(trigobj_pt->at(y),trigobj_pt->at(y)/savePT);
      }
    }
  }
      //if(electron_pt->size()==0)cout<<electron_pt->size()<<'\n';
      //hists[6]->Fill(electron_pt->size());



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

///////////////deltaR
float EventLoopAnalysisTemplate::deltaR(float eta1, float phi1, float eta2, float phi2) {
  float deta = eta1 - eta2;
  float dphi = std::abs(phi1 - phi2);
  if (dphi > 3.14159)
    dphi -= (2 * 3.14159);
  return sqrt(deta * deta + dphi * dphi);
}////Minimal selection




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

  TFile* hfile = new TFile("LW200Trig.root","RECREATE");

  //Save signal region histos
  LW200triggps_1->Write();
  LW200triggps_2->Write();
  LW200triggps_3->Write();
  LW200triggps_4->Write();
  LW200triggps_5->Write();
  LW200triggps_6->Write();
  LW200electron_num->Write();
  LW200electron_pt->Write();
  LW200electron_eta->Write();
  LW200photon_num->Write();
  LW200photon_pt->Write();
  LW200photon_eta->Write();
  LW200PassTrigg->Write();
  LW200Mele_pt->Write();
  LW200Sele_pt->Write();
  LW200MTobj_pt->Write();
  LW200STobj_pt->Write();
  LW200MTobj_ele_dR->Write();
  LW200STobj_ele_dR->Write();
  LW200TO_ele_ptr->Write();
  LW200TO_phot_ptr->Write();
  LW20040GenEle->Write();
  LW20040Ele->Write();


  hfile->Close();


  return 0;

}
