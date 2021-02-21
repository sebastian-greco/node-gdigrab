#pragma once

#include <napi.h>
#include <memory>
#include <Windows.h>
#include <iostream>

class NodeGdigrab : public Napi::ObjectWrap<NodeGdigrab>
{
public:
    NodeGdigrab(const Napi::CallbackInfo&);
    Napi::Value Greet(const Napi::CallbackInfo&);
    Napi::Value Grab(const Napi::CallbackInfo&);
    // Napi::Buffer<char> Grab(const Napi::CallbackInfo&);
    
    static Napi::Function GetClass(Napi::Env);

	~NodeGdigrab();

private:
    std::string _greeterName;
    HDC hScreen;
	HDC hdcMem;
    HBITMAP hBitmap;
	int screenX;
	int screenY;
	int offsetX = 0;
	int offsetY = 0;
	int scaleX;
	int scaleY;

	void loadThings();

    /* struct Work {
	  uv_work_t request;
	  Napi::Persistent<Napi::Function> callback;
      Napi::Persistent callbacl;

	  char* returndata;
	  int returnsize;
	}; */
};
