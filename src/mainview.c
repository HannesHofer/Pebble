#include "utils.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_rect_background_white;
static GBitmap *s_res_bluetooth;
static GBitmap *s_res_bat_low;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_18;
static GFont s_res_gothic_14;
static BitmapLayer *background;
static BitmapLayer *bluetooth;
static BitmapLayer *Battery;
static TextLayer *currenttime;
static TextLayer *Day;
static TextLayer *actDate;
static Layer *batt_level;
static Layer *seconds_top;
static Layer *seconds_right;
static Layer *seconds_bottom;
static TextLayer *debuglayer;
static Layer *seconds_left;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_rect_background_white = gbitmap_create_with_resource(RESOURCE_ID_rect_background_WHITE);
  s_res_bluetooth = gbitmap_create_with_resource(RESOURCE_ID_bluetooth);
  s_res_bat_low = gbitmap_create_with_resource(RESOURCE_ID_BAT_LOW);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // background
  background = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(background, s_res_rect_background_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)background);
  
  // bluetooth
  bluetooth = bitmap_layer_create(GRect(15, 11, 9, 14));
  bitmap_layer_set_bitmap(bluetooth, s_res_bluetooth);
  layer_add_child(window_get_root_layer(s_window), (Layer *)bluetooth);
  
  // Battery
  Battery = bitmap_layer_create(GRect(115, 13, 16, 10));
  bitmap_layer_set_bitmap(Battery, s_res_bat_low);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Battery);
  
  // currenttime
  currenttime = text_layer_create(GRect(0, 50, 144, 53));
  text_layer_set_background_color(currenttime, GColorClear);
  text_layer_set_text_color(currenttime, GColorWhite);
  text_layer_set_text(currenttime, "00:00");
  text_layer_set_text_alignment(currenttime, GTextAlignmentCenter);
  text_layer_set_font(currenttime, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)currenttime);
  
  // Day
  Day = text_layer_create(GRect(0, 27, 144, 27));
  text_layer_set_background_color(Day, GColorClear);
  text_layer_set_text_color(Day, GColorWhite);
  text_layer_set_text(Day, "      ");
  text_layer_set_text_alignment(Day, GTextAlignmentCenter);
  text_layer_set_font(Day, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Day);
  
  // actDate
  actDate = text_layer_create(GRect(0, 102, 145, 28));
  text_layer_set_background_color(actDate, GColorClear);
  text_layer_set_text_color(actDate, GColorWhite);
  text_layer_set_text(actDate, "          ");
  text_layer_set_text_alignment(actDate, GTextAlignmentCenter);
  text_layer_set_font(actDate, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)actDate);
  
  // batt_level
  batt_level = layer_create(GRect(117, 16, 10, 4));
  layer_add_child(window_get_root_layer(s_window), (Layer *)batt_level);
  
  // seconds_top
  seconds_top = layer_create(GRect(0, 0, 144, 8));
  layer_add_child(window_get_root_layer(s_window), (Layer *)seconds_top);
  
  // seconds_right
  seconds_right = layer_create(GRect(136, 11, 10, 148));
  layer_add_child(window_get_root_layer(s_window), (Layer *)seconds_right);
  
  // seconds_bottom
  seconds_bottom = layer_create(GRect(0, 160, 144, 8));
  layer_add_child(window_get_root_layer(s_window), (Layer *)seconds_bottom);
  
  // debuglayer
  debuglayer = text_layer_create(GRect(26, 138, 100, 20));
  text_layer_set_background_color(debuglayer, GColorClear);
  text_layer_set_text_color(debuglayer, GColorWhite);
  text_layer_set_text_alignment(debuglayer, GTextAlignmentCenter);
  text_layer_set_font(debuglayer, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)debuglayer);
  
  // seconds_left
  seconds_left = layer_create(GRect(0, 11, 9, 148));
  layer_add_child(window_get_root_layer(s_window), (Layer *)seconds_left);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(background);
  bitmap_layer_destroy(bluetooth);
  bitmap_layer_destroy(Battery);
  text_layer_destroy(currenttime);
  text_layer_destroy(Day);
  text_layer_destroy(actDate);
  layer_destroy(batt_level);
  layer_destroy(seconds_top);
  layer_destroy(seconds_right);
  layer_destroy(seconds_bottom);
  text_layer_destroy(debuglayer);
  layer_destroy(seconds_left);
  gbitmap_destroy(s_res_rect_background_white);
  gbitmap_destroy(s_res_bluetooth);
  gbitmap_destroy(s_res_bat_low);
}
// END AUTO-GENERATED UI CODE

static void setDate(struct tm *current_time) {
  static char DateBuffer[] = "00/00/0000"; 
  text_layer_set_text(Day, days[current_time->tm_wday]);
  strftime(DateBuffer, sizeof("00/00/0000"), "%d/%m/%Y", current_time);
  text_layer_set_text(actDate, DateBuffer);
}

void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
    static char buffer[] = "00:00";
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    text_layer_set_text(currenttime, buffer);
            
    if (tick_time->tm_min == 0 && tick_time->tm_hour == 0)
      setDate(tick_time);
}

void handle_seconds(struct tm *tick_time, TimeUnits units_changed)
{
  if (tick_time->tm_sec > 8 && tick_time->tm_sec < 24)
    layer_mark_dirty(seconds_right);
  else if (tick_time->tm_sec > 22 && tick_time->tm_sec < 38)
    layer_mark_dirty(seconds_bottom);
  else if (tick_time->tm_sec > 37 && tick_time->tm_sec < 53)
    layer_mark_dirty(seconds_left);
  else if (tick_time->tm_sec < 9 || tick_time->tm_sec > 52)
     layer_mark_dirty(seconds_top);
  
  // update draw color
  if (tick_time->tm_sec == 0)
    drawcolor = not_drawcolor();
    
  // minute update
  if (tick_time->tm_sec == 0)
    handle_tick(tick_time, MINUTE_UNIT);

}

void draw_edge(GContext* ctx, uint8_t edgenr, GColor mydrawcolor) {
  graphics_context_set_fill_color(ctx, mydrawcolor);
  gpath_draw_filled(ctx, edge_path[edgenr]);
}

void draw_rect(GContext* ctx, uint8_t from, uint8_t to, GColor mydrawcolor, bool vertical) {
  GRect drawrect;
  graphics_context_set_fill_color(ctx, mydrawcolor);
  for (uint8_t i=from; i <= to; ++i) {
    if ((i == to || i == from) && (i == 8 || i == 23 || i == 38 || i == 53 )) {
    //if (0) {
      if (i == 8)
        draw_edge(ctx, 0, mydrawcolor);
      else if (i == 23)
        draw_edge(ctx, 1, mydrawcolor);
      else if (i == 38)
        draw_edge(ctx, 2, mydrawcolor);
      else if (i == 53)
        draw_edge(ctx, 3, mydrawcolor);
    } else {
      if (vertical)
        drawrect = GRect(0, seconds_startdraw[i], 8, 3);
      else
        drawrect = GRect(seconds_startdraw[i], 0, 3, 8);
      graphics_fill_rect(ctx, drawrect, 0, GCornerNone);   
    } 
  }
}

void update_secondLayers(Layer *l, GContext* ctx) {
  time_t now = time(NULL);
  static struct tm *current_time;
  current_time = localtime(&now);
  if ( l == seconds_top) {
    if ( current_time->tm_sec < 8) {
      draw_rect(ctx, 53, 59, not_drawcolor(), false);
      draw_rect(ctx, 0, current_time->tm_sec, drawcolor, false);
      draw_rect(ctx, current_time->tm_sec + 1, 8, not_drawcolor(), false);
    } else if (current_time->tm_sec > 52) {
      draw_rect(ctx, 0, 8, drawcolor, false);
      draw_rect(ctx, 53, current_time->tm_sec, drawcolor, false);
      draw_rect(ctx, current_time->tm_sec +1, 59, not_drawcolor(), false);
    } else {
      draw_rect(ctx, 0, 8, drawcolor, false);
      draw_rect(ctx, 53, 59, not_drawcolor(), false);
    }
  } else if ( l == seconds_bottom) {
    if (current_time->tm_sec > 38 || current_time->tm_sec < 23) {
      GColor mycolor = not_drawcolor();
      if (current_time->tm_sec > 38)
        mycolor = drawcolor;
      draw_rect(ctx, 23, 38, mycolor, false);
    } else {
       draw_rect(ctx, 23, current_time->tm_sec, drawcolor, false);
       draw_rect(ctx, current_time->tm_sec +1, 38, not_drawcolor(), false);
    }
  } else if (l == seconds_right) {
     if (current_time->tm_sec > 22 || current_time->tm_sec < 9){
       GColor mycolor = not_drawcolor();
       if (current_time->tm_sec > 22)
          mycolor = drawcolor;
       draw_rect(ctx, 9, 22, mycolor, true);
     } else {
        draw_rect(ctx, 9, current_time->tm_sec, drawcolor, true);
        draw_rect(ctx, current_time->tm_sec +1, 22, not_drawcolor(), true);
     }
  } else if (l == seconds_left) {
     if (current_time->tm_sec < 39 || current_time->tm_sec > 52){
       GColor mycolor = not_drawcolor();
       if (current_time->tm_sec > 52)
         mycolor = drawcolor;
       draw_rect(ctx, 39, 52, mycolor, true);
     } else {
       draw_rect(ctx, 39, current_time->tm_sec, drawcolor, true);
       draw_rect(ctx, current_time->tm_sec +1, 52, not_drawcolor(), true);
     }
  }
}

void handle_bluetooth(bool connected) {
  if (connected)
    bitmap_layer_set_bitmap(bluetooth, s_res_bluetooth);
  else {
    bitmap_layer_set_bitmap(bluetooth, s_res_nobluetooth);
  }
}

void handle_battery(BatteryChargeState chargestate) {
  bat_level = chargestate.charge_percent;
  layer_mark_dirty(batt_level);
}

void update_bat(Layer *l, GContext* ctx) {
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_fill_rect(ctx, GRect(0, 0, bat_level/10, 4), 0, GCornerNone);
  
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, GRect(bat_level/10, 0, 10, 4), 0, GCornerNone);
}


static void init_data() {
  time_t now = time(NULL);
  struct tm *current_time;
  current_time = localtime(&now);
  
  // create edge path  
  for (int i=0;i<4;i++)
    edge_path[i] = gpath_create(&BOLT_PATH_INFO);
  
  gpath_move_to(edge_path[0], GPoint(143, 7));
  gpath_rotate_to(edge_path[0], TRIG_MAX_ANGLE * 180 / 360);
  gpath_move_to(edge_path[1], GPoint(136, 7));
  gpath_rotate_to(edge_path[1], TRIG_MAX_ANGLE * 270 / 360);
  gpath_move_to(edge_path[3], GPoint(7, 0));
  gpath_rotate_to(edge_path[3], TRIG_MAX_ANGLE * 90 / 360);
  
  // create battery layer
  layer_set_update_proc(batt_level, (LayerUpdateProc)update_bat);
  layer_set_update_proc(seconds_top, (LayerUpdateProc)update_secondLayers);
  layer_set_update_proc(seconds_bottom, (LayerUpdateProc)update_secondLayers);
  layer_set_update_proc(seconds_left, (LayerUpdateProc)update_secondLayers);
  layer_set_update_proc(seconds_right, (LayerUpdateProc)update_secondLayers);
  
  // first refresh
  handle_tick(current_time, MINUTE_UNIT);  
  setDate(current_time);
  handle_bluetooth(bluetooth_connection_service_peek());
  handle_battery(battery_state_service_peek());
  
  //register events
  bluetooth_connection_service_subscribe(handle_bluetooth);
  //tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) handle_tick);
  tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) handle_seconds);
  battery_state_service_subscribe(handle_battery);
  
  // custom resources
  s_res_nobluetooth = gbitmap_create_with_resource(RESOURCE_ID_nobluetooth); 
}

static void handle_window_unload(Window* window) {
  bluetooth_connection_service_unsubscribe();
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  destroy_ui();
  // custom resources
  gbitmap_destroy(s_res_nobluetooth);
}

void show_mainview(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

int main(void) {
  show_mainview();
  init_data();
  app_event_loop();
}