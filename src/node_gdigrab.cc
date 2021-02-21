#include "node_gdigrab.h"

using namespace Napi;

NodeGdigrab::NodeGdigrab(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
		
    
}

void NodeGdigrab::loadThings() {
	this->hScreen = GetDC(0);
  this->hdcMem = CreateCompatibleDC(hScreen);
  this->screenX = GetDeviceCaps(hScreen, HORZRES);
  this->screenY = GetDeviceCaps(hScreen, VERTRES);
  
  this->scaleY = this->screenY;
  this->scaleX = this->screenX;

  this->hBitmap = CreateCompatibleBitmap(this->hScreen, this->screenX, this->screenY);
}

// Napi::Buffer<char> NodeGdigrab::Grab(const Napi::CallbackInfo& info) {
Napi::Value NodeGdigrab::Grab(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    this->loadThings();

    HGDIOBJ hOld = SelectObject(this->hdcMem, this->hBitmap);

    //std::cout << "Hello there\n";
    
		BitBlt(this->hdcMem, 0, 0, this->screenX, this->screenY, this->hScreen, this->offsetX, this->offsetY, SRCCOPY);
		SelectObject(this->hdcMem, hOld);


		BITMAPINFO bmi = {0};
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biWidth = this->scaleX;
		bmi.bmiHeader.biHeight = -this->scaleY;

    int size = 4 * this->scaleX * this->scaleY;
    char* data = (char*)malloc(size);
		
		
		GetDIBits(this->hdcMem, this->hBitmap, 0, this->scaleY, data, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

    DeleteDC(this->hdcMem);
    DeleteObject(this->hBitmap);

    Napi::Buffer<char> buffer = Napi::Buffer<char>::Copy(env, data, size);
    free(data);
    return buffer;
}

Napi::Value NodeGdigrab::Greet(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "You need to introduce yourself to greet")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String name = info[0].As<Napi::String>();

    printf("Hello %s\n", name.Utf8Value().c_str());

    return Napi::String::New(env, this->_greeterName);
}

Napi::Function NodeGdigrab::GetClass(Napi::Env env) {
    return DefineClass(env, "NodeGdigrab", {
        NodeGdigrab::InstanceMethod("greet", &NodeGdigrab::Greet),
        NodeGdigrab::InstanceMethod("grab", &NodeGdigrab::Grab),
    });
}

NodeGdigrab::~NodeGdigrab() {
  //std::cout << "static destructor\n";
  //ReleaseDC(GetDesktopWindow(),this->hScreen);
  //DeleteDC(this->hdcMem);
  //DeleteObject(this->hBitmap);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "NodeGdigrab");
    exports.Set(name, NodeGdigrab::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
