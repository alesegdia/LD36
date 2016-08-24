#include "assets.h"
#include <iostream>


Assets* Assets::instance = nullptr;

Assets::Assets()
{

}

Assets::~Assets()
{
	// FREE RESOURCES!!

}

void Assets::Initialize()
{
	Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}
