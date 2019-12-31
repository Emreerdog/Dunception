// Fill out your copyright notice in the Description page of Project Settings.

#include "AMainHUD.h"

AAMainHUD::AAMainHUD() {
	ControlPanelVisibility = ESlateVisibility::Hidden;
}

void AAMainHUD::EnablePanel()
{
	ControlPanelVisibility = ESlateVisibility::Visible;
}

void AAMainHUD::DisablePanel()
{
	
	ControlPanelVisibility = ESlateVisibility::Hidden;
}
