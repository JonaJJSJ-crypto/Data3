# Implementation of the plotting step of the analysis
#
# The plotting combines the histograms to plots which allow us to study the
# inital dataset based on observables motivated through physics.

import ROOT
ROOT.gROOT.SetBatch(True)


# Declare a human-readable label for each variable
labels = {
        "ppoint": "SV Paralelity: displacement & Total momentum",
        "ppointS": "SV Paralelity sign: displacement & Total momentum",
        "npv": "Number of primary vertices",
        #"JetMass": "DiJets invariant mass",
        #"LWMass": "LW invariant mass",
        "nsv": "Number od secondary vertices",
        "svd": "Secondary vertex displacement",
        "BSd": "Secondary vertex Distance to Bsp",
        "BSdChi2norm": "Secondary vertex Distance/Norm to Bsp",}
'''
        "Elept": "Electron Tranversal momentum",
        "DieledR": "Di electron delta R",
        "LWdR": "DiJet+electron delta R",
        "DiJetdR": "DiJet delta R",
        "BJetPt": "Most energetic jet tranversal momentum",
        "SBJetPt": "Most energetic jet transversal momentum",
        "NJet": "Number of Jets",
        "NEle": "Number of Electrons",
        "BSd": "Secondary vertex Distance to Bsp",
        "BSdChi2norm": "Secondary vertex Distance/Norm to Bsp",
        "EleJet1DR": "Electron closest Jet DR",
        "EleJet2DR": "Electron second closest Jet DR",
        "JetJet1DR": "Jet closest Jet DR",
        "JetJet2DR": "Jet second closest Jet DR",
        "JetJetFDR": "Jet further Jet DR",
        #"eta_2": "Tau #eta",
        #"m_vis": "Visible di-tau mass / GeV",
        }'''

# Specify the color for each process
colors = {
        #"ggH": ROOT.TColor.GetColor("#BF2229"),
        "LW200": ROOT.TColor.GetColor("#00A88F"),
        "TT": ROOT.TColor.GetColor(155, 152, 204),
        "W": ROOT.TColor.GetColor(222, 90, 106),
        "QCD":  ROOT.TColor.GetColor(250, 202, 255),
        "ZLL": ROOT.TColor.GetColor(248, 206, 104),
        #"WW" : ROOT.TColor.GetColor(100, 192, 232),
        #"WZ" : ROOT.TColor.GetColor(500, 150, 104),
        #"ttZ" : ROOT.TColor.GetColor(238, 286, 134),
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
    tfile = ROOT.TFile("histograms.root", "READ")

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
    LW200 = getHistogram(tfile, "TF_LW200", variable)

    W = getHistogram(tfile, "TF_W1J", variable)
    W2J = getHistogram(tfile, "TF_W2J", variable)
    W3J = getHistogram(tfile, "TF_W3J", variable)
    W.Add(W2J)
    W.Add(W3J)

    TT = getHistogram(tfile, "TF_TT", variable)

    ZLL = getHistogram(tfile, "TF_ZLL", variable)

    #WW = getHistogram(tfile, "TF_WW", variable)

    #WZ = getHistogram(tfile, "TF_WZ", variable)

    #ttZ = getHistogram(tfile, "TF_ttZ", variable)

    # Data
    data = getHistogram(tfile, "TF_dataRunB", variable)
    dataRunC = getHistogram(tfile, "TF_dataRunC", variable)
    data.Add(dataRunC)

    # Data-driven QCD estimation
    QCD = getHistogram(tfile, "TF_dataRunB", variable, "_cr")
    QCDRunC = getHistogram(tfile, "TF_dataRunC", variable, "_cr")
    QCD.Add(QCDRunC)
    for name in ["TF_W1J", "TF_W2J", "TF_W3J", "TF_TT", "TF_ZLL"]:
        ss = getHistogram(tfile, name, variable, "_cr")
        QCD.Add(ss, -1.0)
    for i in range(1, QCD.GetNbinsX() + 1):
        if QCD.GetBinContent(i) < 0.0:
            QCD.SetBinContent(i, 0.0)
    QCDScaleFactor = 0.9
    QCD.Scale(QCDScaleFactor)

    # Draw histograms
    data.SetMarkerStyle(20)
    data.SetLineColor(ROOT.kBlack)
    #ggH.SetLineColor(colors["ggH"])
    LW200.SetMarkerStyle(20)
    LW200.SetLineColor(colors["LW200"])

    #scale_ggH = 10.0
    #ggH.Scale(scale_ggH)
    if variable == "svd" or variable == "nsv":
        scale_LW200 = 100.0
        LW200.Scale(scale_LW200)
    elif variable == "EleJet1DR" or variable == "EleJet2DR" or variable == "JetJet1DR" or variable == "JetJet2DR" or variable == "JetJetFDR":
        scale_LW200 = 1.0
        LW200.Scale(scale_LW200)
    else:
        scale_LW200 = 10000.0
        LW200.Scale(scale_LW200)

    LW200.SetLineWidth(3)

    #for x in [LW200]:
        #x.SetLineWidth(3)


    for x, l in [(TT, "TT"), (ZLL, "ZLL"), (W, "W"), (QCD, "QCD")]:#,(WW, "WW"), (WZ, "WZ"), (ttZ, "ttZ")]:
        x.SetLineWidth(0)
        x.SetFillColor(colors[l])
    #ZLL.SetLineWidth(0)
    #ZLL.SetFillColor(colors["ZLL"])


    stack = ROOT.THStack("", "")


    for x in [QCD, TT, W, ZLL]:
#    for x in [TT, W, ZLL]:#, WW, WZ, ttZ]:
        stack.Add(x)
    #stack.Add(ZLL)

    c = ROOT.TCanvas("", "", 600, 600)
    #c.SetLogy()
    #stack.Draw("E3")
    stack.Draw("hist")

    sum = ZLL.Clone()
    sum.Add(TT)
    sum.Add(W)
    sum.Add(QCD)

    if variable == "ppoint":
        # Simulation
        #ggH = getHistogram(tfile, "ggH", variable)
        Uncert_LW200 = getHistogram(tfile, "TF_LW200", variable,"_uncert")

        Uncert_W = getHistogram(tfile, "TF_W1J", variable,"_uncert")
        Uncert_W2J = getHistogram(tfile, "TF_W2J", variable,"_uncert")
        Uncert_W3J = getHistogram(tfile, "TF_W3J", variable,"_uncert")
        Uncert_W.Add(Uncert_W2J)
        Uncert_W.Add(Uncert_W3J)

        Uncert_TT = getHistogram(tfile, "TF_TT", variable,"_uncert")

        Uncert_ZLL = getHistogram(tfile, "TF_ZLL", variable,"_uncert")

        #WW = getHistogram(tfile, "TF_WW", variable)

        #WZ = getHistogram(tfile, "TF_WZ", variable)

        #ttZ = getHistogram(tfile, "TF_ttZ", variable)

        # Data
        Uncert_data = getHistogram(tfile, "TF_dataRunB", variable,"_uncert")
        Uncert_dataRunC = getHistogram(tfile, "TF_dataRunC", variable,"_uncert")
        Uncert_data.Add(Uncert_dataRunC)

        # Data-driven QCD estimation
        Uncert_QCD = getHistogram(tfile, "TF_dataRunB", variable,"_uncert")
        Uncert_QCDRunC = getHistogram(tfile, "TF_dataRunC", variable,"_uncert")
        Uncert_QCD.Add(Uncert_QCDRunC)
        for name in ["TF_W1J", "TF_W2J", "TF_W3J", "TF_TT", "TF_ZLL"]:
            ss = getHistogram(tfile, name, variable,"_uncert")
            Uncert_QCD.Add(ss, -1.0)
        for i in range(1, Uncert_QCD.GetNbinsX() + 1):
            if Uncert_QCD.GetBinContent(i) < 0.0:
                Uncert_QCD.SetBinContent(i, 0.0)
        Uncert_QCDScaleFactor = 0.9
        Uncert_QCD.Scale(Uncert_QCDScaleFactor)


        Uncert_sum = Uncert_ZLL.Clone()
        Uncert_sum.Sumw2()
        Uncert_sum.Add(Uncert_TT)
        Uncert_sum.Add(Uncert_W)
        Uncert_sum.Add(Uncert_QCD)




        for i in range(1, Uncert_sum.GetNbinsX() + 1):
            error = Uncert_sum.GetBinError(i)
            print(error)
            sum.SetBinError(i,error)
        #sum.SetFillColor(0)
        sum.SetFillStyle(3004)
        sum.SetLineWidth(1)
        #sum.SetFillStyle(3365)
        sum.SetFillColorAlpha(1, 0.35)
        sum.SetLineColor(2)
        sum.SetLineStyle(1)
        sum.SetLineWidth(1)
        sum.Draw("LE2 SAME")

    if variable == "svd":
        for i in range(1, sum.GetNbinsX() + 1):
            error = 0.01*sum.GetBinContent(i)
            print(error)
            sum.SetBinError(i,error)
        #sum.SetFillColor(0)
        sum.SetFillStyle(3004)
        sum.SetLineWidth(1)
        #sum.SetFillStyle(3365)
        sum.SetFillColorAlpha(1, 0.35)
        sum.SetLineColor(2)
        sum.SetLineStyle(1)
        sum.SetLineWidth(1)
        sum.Draw("LE2 SAME")

    name = data.GetTitle()
    if name in labels:
        title = labels[name]
    else:
        title = name
    stack.GetXaxis().SetTitle(title)
    stack.GetYaxis().SetTitle("N_{Events}")
    stack.SetMaximum(max(stack.GetMaximum(), data.GetMaximum()) * 1.4)
    stack.SetMinimum(1.0)

    #ggH.IST SAME")
    LW200.Draw("HIST SAME")

    data.Draw("E1P SAME")

    # Add legend
    legend = ROOT.TLegend(0.65, 0.73, 0.90, 0.88)
    legend.SetNColumns(1)
    #legend.AddEntry(WW, "WW", "f")
    #legend.AddEntry(WZ, "WZ", "f")
    #legend.AddEntry(ttZ, "t#bar{t}Z", "f")
    legend.AddEntry(ZLL, "Z#rightarrowll", "f")
    legend.AddEntry(W, "W+jets", "f")
    legend.AddEntry(TT, "t#bar{t}", "f")
    legend.AddEntry(QCD, "QCD multijet", "f")
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
    if variable == "svd" or variable == "nsv" or variable == "ppoint" or variable == "BSdChi2norm":
    #if variable == "svd" or variable == "nsv" or variable == "BSdChi2norm":
        c.SetLogy()
        c.SaveAs("%s.pdf" % ("PDF/"+variable+"_1_TF"))
        c.SaveAs("%s.png" % ("PNG/"+variable+"_1_TF"))
    else:
        c.SaveAs("%s.pdf" % ("PDF/"+variable+"_1_TF"))
        c.SaveAs("%s.png" % ("PNG/"+variable+"_1_TF"))

# Loop over all variable names and make a plot for each
if __name__ == "__main__":
    for variable in labels.keys():
        main(variable)
