#pragma once
#include "MessageQueue.hpp"
#include "Epoll.h"

MessageQueue<int> requestQueue;
Epoll epoll;
