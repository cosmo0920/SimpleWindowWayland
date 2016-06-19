#pragma once

#include <stdint.h>
#include <wayland-client.h>


class WaylandCore {
public:
  WaylandCore( int width, int height, const char* title );
  WaylandCore();
  ~WaylandCore();
  
  void waitEvents();
  void pollEvents();
  
  bool isShouldClose();

  int  getWidth() const   { return mWidth; }
  int  getHeight() const  { return mHeight; }
  void redrawWindow();
private:
  void createWindow( int width, int height, const char* title );  
  void setup_registry_handlers();
  
private:

  static void seat_handle_capabilities(
                void* data,
                wl_seat* seat, 
                uint32_t caps );
public:
  void registry_listener_global( wl_registry* reg, uint32_t name, const char* interface, uint32_t version );
  void registry_listener_global_remove( wl_registry* reg, uint32_t name );

  // 入力に関するイベントハンドラ群.
  void seat_listener_capabilities( wl_seat* seat, uint32_t caps );
  void pointer_handler_enter_leave( bool is_enter, wl_surface* surface, double cx, double cy );
  void pointer_handler_move( double cx, double cy );
  void pointer_handler_button( uint32_t button, uint32_t status );
  void pointer_handler_wheel( uint32_t axis, double val );
private:
  wl_display* mDisplay;
  wl_registry* mRegistry;
  wl_compositor* mCompositor;
  wl_shell*   mShell;
  wl_shm* mShm;
  wl_seat* mSeat;
  wl_pointer* mPointer;
  wl_keyboard* mKeyboard;
  
  struct Surface {
    wl_surface* surface;
    wl_buffer*  buffer;
    void*       memory;
  } mSurface;
  wl_shell_surface* mShellSurface;

  bool mShouldClose;
  int  mWidth, mHeight;
};
