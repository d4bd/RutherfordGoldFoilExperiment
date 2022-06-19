// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{
	gROOT->Reset();
	gROOT->SetStyle("Plain");
	
	// Draw histos filled by Geant4 simulation 
	//   

	// Open file filled by Geant4 simulation 
	TFile f("FPR.root");

	// Create a canvas and divide it into 2x2 pads
	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	//Splits the rapresentation
	c1->Divide(2,2);
	
	//Draw histogram in the pad 1
	c1->cd(1);
	gPad->SetLogy(1);
	TH1D* hist1 = (TH1D*)f.Get("ScreenHit");
	hist1->GetYaxis()->SetTitle("Number of Hits");
	hist1->GetXaxis()->SetTitle("Screen Number");
	hist1->Draw("HIST");

	//Draw histogram in the pad 2
	c1->cd(2);
	gPad->SetLogy(1);
	TH1D* hist2 = (TH1D*)f.Get("AngleHit");
	hist2->GetYaxis()->SetTitle("Number of Hits");
	hist2->GetXaxis()->SetTitle("Scattering angle (rad)");
	hist2->Draw("HIST");

	//Draw histogram in the pad 3
	c1->cd(3);
	TH1D* hist3 = (TH1D*)f.Get("ScreenHitIMP");
	hist3->GetYaxis()->SetTitle("Number of Hits");
	hist3->GetXaxis()->SetTitle("Screen Number");
	hist3->Draw("HIST");

	//Draw histogram in the pad 4
	c1->cd(4);
	TH1D* hist4 = (TH1D*)f.Get("AngleHitIMP");
	hist4->GetYaxis()->SetTitle("Number of Hits");
	hist4->GetXaxis()->SetTitle("Scattering angle (rad)");
	hist4->Draw("HIST");
}  
