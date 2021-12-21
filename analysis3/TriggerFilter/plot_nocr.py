# Implementation of the plotting step of the analysis
#
# The plotting combines the histograms to plots which allow us to study the
# inital dataset based on observables motivated through physics.

import ROOT
ROOT.gROOT.SetBatch(True)


# Declare a human-readable label for each variable
labels = {
        "NF_npv": "NF Number of primary vertices",
        "NF_JetMass": "NF DiJets invariant mass",
        "NF_LWMass": "NF LW invariant mass",
        "NF_nsv": "NF Number od secondary vertices",
        "NF_svd": "NF Secondary vertex displacement",
        "NF_Elept": "NF Electron Tranversal momentum",
        "NF_DieledR": "NF Di electron delta R",
        "NF_LWdR": "NF DiJet+electron delta R",
        "NF_DiJetdR": "NF DiJet delta R",
        "NF_BJetPt": "NF Most energetic jet tranversal momentum",
        "NF_SBJetPt": "NF Most energetic jet transversal momentum",
        "NF_NJet": "NF Number of Jets",
        "NF_NEle": "NF Number of Electrons",
        "TF_npv": "TF Number of primary vertices",
        "TF_JetMass": "TF DiJets invariant mass",
        "TF_LWMass": "TF LW invariant mass",
        "TF_nsv": "TF Number od secondary vertices",
        "TF_svd": "TF Secondary vertex displacement",
        "TF_Elept": "TF Electron Tranversal momentum",
        "TF_DieledR": "TF Di electron delta R",
        "TF_LWdR": "TF DiJet+electron delta R",
        "TF_BJetPt": "TF Most energetic jet tranversal momentum",
        "TF_SBJetPt": "TF Most energetic jet transversal momentum",
        "TF_NJet": "TF Number of Jets",
        "TF_NEle": "TF Number of Electrons",
        "TO_npv": "TO Number of primary vertices",
        "TO_JetMass": "TO DiJets invariant mass",
        "TO_LWMass": "TO LW invariant mass",
        "TO_nsv": "TO Number od secondary vertices",
        "TO_svd": "TO Secondary vertex displacement",
        "TO_Elept": "TO Electron Tranversal momentum",
        "TO_DieledR": "TO Di electron delta R",
        "TO_LWdR": "TO DiJet+electron delta R",
        "TO_DiJetdR": "TO DiJet delta R",
        "TO_BJetPt": "TO Most energetic jet tranversal momentum",
        "TO_SBJetPt": "TO Most energetic jet transversal momentum",
        "TO_NJet": "TO Number of Jets",
        "TO_NEle": "TO Number of Electrons",
        "HQ_npv": "HQ Number of primary vertices",
        "HQ_JetMass": "HQ DiJets invariant mass",
        "HQ_LWMass": "HQ LW invariant mass",
        "HQ_nsv": "HQ Number od secondary vertices",
        "HQ_svd": "HQ Secondary vertex displacement",
        "HQ_Elept": "HQ Electron Tranversal momentum",
        "HQ_DieledR": "HQ Di electron delta R",
        "HQ_LWdR": "HQ DiJet+electron delta R",
        "HQ_DiJetdR": "HQ DiJet delta R",
        "HQ_BJetPt": "HQ Most energetic jet tranversal momentum",
        "HQ_SBJetPt": "HQ Most energetic jet transversal momentum",
        "HQ_NJet": "HQ Number of Jets",
        "HQ_NEle": "HQ Number of Electrons",

        #"eta_2": "Tau #eta",
        #"m_vis": "Visible di-tau mass / GeV",
        }

# Specify the color for each process
colors = {
        #"ggH": ROOT.TColor.GetColor("#BF2229"),
        "LW200": ROOT.TColor.GetColor("#00A88F"),
        "TT": ROOT.TColor.GetColor(155, 152, 204),
        "W": ROOT.TColor.GetColor(222, 90, 106),
        "QCD":  ROOT.TColor.GetColor(250, 202, 255),
        "ZLL": ROOT.TColor.GetColor(248, 206, 104),
        "WW" : ROOT.TColor.GetColor(100, 192, 232),
        "WZ" : ROOT.TColor.GetColor(500, 150, 104),
        "TTZ" : ROOT.TColor.GetColor(238, 286, 134),
        #"ZLL": ROOT.TColor.GetColor(100, 192, 232),
        #"ZTT": ROOT.TColor.GetColor(248, 206, 104),
        }

# Retrieve a histogram from the input file based on the process and the variable
# name
def getHistogram(tfile, name, variable, tag=""):
    print (name)
    print (variable)
    name = "%s_%s%s" % (name, variable, tag)
    h = tfile.Get(name)
    if not h:
        raise Exception("Failed to load histogram %s." % (name))
    return h

# Main function of the plotting step
#
# The major part of the code below is dedicated to define a nice-looking layout.
# The full version of this analysis continas the estimation of QCD background
def main(variable):
    tfile = ROOT.TFile("histogramsTrigg.root", "READ")

    # Styles
    ROOT.gStyle.SetOptStat(0)

    ROOT.gStyle.SetCanvasBorderMode(0)
    ROOT.gStyle.SetCanvasColor(ROOT.kWhite)
    ROOT.gStyle.SetCanvasDefH(600)
    ROOT.gStyle.SetCanvasDefW(600)
    ROOT.gStyle.SetCanvasDefX(0)
    ROOT.gStyle.SetCanvasDefY(0)

    ROOT.gStyle.SetPadTopMargin(0.08)
    ROOT.gStyle.SetPadBottomMargin(0.13)
    ROOT.gStyle.SetPadLeftMargin(0.16)
    ROOT.gStyle.SetPadRightMargin(0.05)

    ROOT.gStyle.SetHistLineColor(1)
    ROOT.gStyle.SetHistLineStyle(0)
    ROOT.gStyle.SetHistLineWidth(1)
    ROOT.gStyle.SetEndErrorSize(2)
    ROOT.gStyle.SetMarkerStyle(20)

    ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetTitleFont(42)
    ROOT.gStyle.SetTitleColor(1)
    ROOT.gStyle.SetTitleTextColor(1)
    ROOT.gStyle.SetTitleFillColor(10)
    ROOT.gStyle.SetTitleFontSize(0.05)

    ROOT.gStyle.SetTitleColor(1, "XYZ")
    ROOT.gStyle.SetTitleFont(42, "XYZ")
    ROOT.gStyle.SetTitleSize(0.05, "XYZ")
    ROOT.gStyle.SetTitleXOffset(1.00)
    ROOT.gStyle.SetTitleYOffset(1.60)

    ROOT.gStyle.SetLabelColor(1, "XYZ")
    ROOT.gStyle.SetLabelFont(42, "XYZ")
    ROOT.gStyle.SetLabelOffset(0.007, "XYZ")
    ROOT.gStyle.SetLabelSize(0.04, "XYZ")

    ROOT.gStyle.SetAxisColor(1, "XYZ")
    ROOT.gStyle.SetStripDecimals(True)
    ROOT.gStyle.SetTickLength(0.03, "XYZ")
    ROOT.gStyle.SetNdivisions(510, "XYZ")
    ROOT.gStyle.SetPadTickX(1)
    ROOT.gStyle.SetPadTickY(1)

    ROOT.gStyle.SetPaperSize(20., 20.)
    ROOT.gStyle.SetHatchesLineWidth(5)
    ROOT.gStyle.SetHatchesSpacing(0.05)

    #ROOT.TGaxis.SetExponentOffset(-0.08, 0.01, "Y")


    # Simulation
    #ggH = getHistogram(tfile, "ggH", variable)
    LW200 = getHistogram(tfile, "LW200", variable)

    W = getHistogram(tfile, "W1J", variable)
    W2J = getHistogram(tfile, "W2J", variable)
    W3J = getHistogram(tfile, "W3J", variable)
    W.Add(W2J)
    W.Add(W3J)

    TT = getHistogram(tfile, "TT", variable)

    ZLL = getHistogram(tfile, "ZLL", variable)

    WW = getHistogram(tfile, "WW", variable)

    WZ = getHistogram(tfile, "WZ", variable)

    TTZ = getHistogram(tfile, "TTZ", variable)

    # Data
    data = getHistogram(tfile, "dataRunB", variable)
    dataRunC = getHistogram(tfile, "dataRunC", variable)
    data.Add(dataRunC)

    # Data-driven QCD estimation
#    QCD = getHistogram(tfile, "dataRunB", variable, "_cr")
#    QCDRunC = getHistogram(tfile, "dataRunC", variable, "_cr")
#    QCD.Add(QCDRunC)
#    for name in ["W1J", "W2J", "W3J", "TT", "ZLL"]:
#        ss = getHistogram(tfile, name, variable, "_cr")
#        QCD.Add(ss, -1.0)
#    for i in range(1, QCD.GetNbinsX() + 1):
#        if QCD.GetBinContent(i) < 0.0:
#            QCD.SetBinContent(i, 0.0)
#    QCDScaleFactor = 0.80
#    QCD.Scale(QCDScaleFactor)

    # Draw histograms
    data.SetMarkerStyle(20)
    data.SetLineColor(ROOT.kBlack)
    #ggH.SetLineColor(colors["ggH"])
    LW200.SetMarkerStyle(20)
    LW200.SetLineColor(colors["LW200"])

    #scale_ggH = 10.0
    #ggH.Scale(scale_ggH)
    if variable == "svd" or variable == "nsv" :
        scale_LW200 = 100.0
        LW200.Scale(scale_LW200)
    else:
        scale_LW200 = 10000.0
        LW200.Scale(scale_LW200)

    LW200.SetLineWidth(3)

    #for x in [LW200]:
        #x.SetLineWidth(3)


    for x, l in [(TT, "TT"), (ZLL, "ZLL"), (W, "W"),(WW, "WW"), (WZ, "WZ"), (TTZ, "TTZ")]:
        x.SetLineWidth(0)
        x.SetFillColor(colors[l])
    #ZLL.SetLineWidth(0)
    #ZLL.SetFillColor(colors["ZLL"])


    stack = ROOT.THStack("", "")
#    for x in [QCD, TT, W, ZLL]:
    for x in [TT, W, ZLL, WW, WZ, TTZ]:
        stack.Add(x)
    #stack.Add(ZLL)

    c = ROOT.TCanvas("", "", 600, 600)
    #c.SetLogy()
    stack.Draw("hist")
    name = data.GetTitle()
    if name in labels:
        title = labels[name]
    else:
        title = name
    stack.GetXaxis().SetTitle("title;lenght [cm];Arb.Units")
    stack.GetYaxis().SetTitle("N_{Events}")
    stack.SetMaximum(max(stack.GetMaximum(), data.GetMaximum()) * 1.4)
    stack.SetMinimum(1.0)
    print(title)

    #ggH.Draw("HIST SAME")
    LW200.Draw("HIST SAME")

    data.Draw("E1P SAME")

    # Add legend
    legend = ROOT.TLegend(0.4, 0.73, 0.90, 0.88)
    legend.SetNColumns(2)
    legend.AddEntry(WW, "WW", "f")
    legend.AddEntry(WZ, "WZ", "f")
    legend.AddEntry(TTZ, "t#bar{t}Z", "f")
    legend.AddEntry(ZLL, "Z#rightarrowll", "f")
    legend.AddEntry(W, "W+jets", "f")
    legend.AddEntry(TT, "t#bar{t}", "f")
    #legend.AddEntry(QCD, "QCD multijet", "f")
    #legend.AddEntry(ggH, "gg#rightarrowH (x%.0f)"%scale_ggH, "l")
    legend.AddEntry(LW200, "lwe#rightarrowZe (x%.0f)"%scale_LW200, "l")
    legend.AddEntry(data, "Data", "lep")
    legend.SetBorderSize(0)
    legend.Draw()


    # Add title
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04)
    latex.SetTextFont(42)
    latex.DrawLatex(0.6, 0.935, "11.5 fb^{-1} (2012, 8 TeV)")
    latex.DrawLatex(0.24, 0.935, "#bf{CMS Open Data}")

    # Save
    if variable == "svd" or variable == "nsv":
        c.SetLogy()
        c.SaveAs("%s.pdf" % (variable))
        c.SaveAs("%s.png" % (variable))
    else:
        c.SaveAs("%s.pdf" % (variable))
        c.SaveAs("%s.png" % (variable))

# Loop over all variable names and make a plot for each
if __name__ == "__main__":
    for variable in labels.keys():
        main(variable)
