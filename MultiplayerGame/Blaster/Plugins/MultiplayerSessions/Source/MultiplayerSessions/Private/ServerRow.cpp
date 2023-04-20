// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/Button.h"
#include "Menu.h"

void UServerRow::Setup(UMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
}
