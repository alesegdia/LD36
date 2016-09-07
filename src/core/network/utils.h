#pragma once

#include "client.h"
#include <cstdio>

Client::SharedPtr netutils_create_host_from_args( int argc, char** argv );
