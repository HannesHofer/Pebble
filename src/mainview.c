#include "communication.h"
#include "config.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_rect_background_white;
static GBitmap *s_res_bluetooth;
static GBitmap *s_res_bat_low;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_18;
static GBitmap *s_res_sunrise;
static GBitmap *s_res_sunset;
static GBitmap *s_res_sunrise_stored;
static GBitmap *s_res_sunset_stored;
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
static Layer *seconds_left;
static BitmapLayer *sunrise;
static BitmapLayer *sunset;
static TextLayer *sunrisetime;
static TextLayer *sunsettime;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_rect_background_white = gbitmap_create_with_resource(RESOURCE_ID_rect_background_WHITE);
  s_res_bluetooth = gbitmap_create_with_resource(RESOURCE_ID_bluetooth);
  s_res_bat_low = gbitmap_create_with_resource(RESOURCE_ID_BAT_LOW);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_sunrise = gbitmap_create_with_resource(RESOURCE_ID_sunrise);
  s_res_sunset = gbitmap_create_with_resource(RESOURCE_ID_sunset);
  s_res_sunrise_stored = gbitmap_create_with_resource(RESOURCE_ID_sunrise_stored);
  s_res_sunset_stored = gbitmap_create_with_resource(RESOURCE_ID_sunset_stored);
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
  currenttime = text_layer_create(GRect(0, 49, 144, 53));
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
  actDate = text_layer_create(GRect(0, 102, 144, 28));
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
  
  // seconds_left
  seconds_left = layer_create(GRect(0, 11, 9, 148));
  layer_add_child(window_get_root_layer(s_window), (Layer *)seconds_left);
  
  // sunrise
  sunrise = bitmap_layer_create(GRect(21, 136, 8, 13));
  bitmap_layer_set_bitmap(sunrise, s_res_sunrise_stored);
  layer_add_child(window_get_root_layer(s_window), (Layer *)sunrise);
  
  // sunset
  sunset = bitmap_layer_create(GRect(87, 135, 8, 13));
  bitmap_layer_set_bitmap(sunset, s_res_sunset_stored);
  layer_add_child(window_get_root_layer(s_window), (Layer *)sunset);
  
  // sunrisetime
  sunrisetime = text_layer_create(GRect(32, 133, 31, 16));
  text_layer_set_background_color(sunrisetime, GColorClear);
  text_layer_set_text_color(sunrisetime, GColorWhite);
  text_layer_set_text(sunrisetime, "     ");
  text_layer_set_font(sunrisetime, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)sunrisetime);
  
  // sunsettime
  sunsettime = text_layer_create(GRect(98, 132, 29, 17));
  text_layer_set_background_color(sunsettime, GColorClear);
  text_layer_set_text_color(sunsettime, GColorWhite);
  text_layer_set_text(sunsettime, "     ");
  text_layer_set_font(sunsettime, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)sunsettime);
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
  layer_destroy(seconds_left);
  bitmap_layer_destroy(sunrise);
  bitmap_layer_destroy(sunset);
  text_layer_destroy(sunrisetime);
  text_layer_destroy(sunsettime);
  gbitmap_destroy(s_res_rect_background_white);
  gbitmap_destroy(s_res_bluetooth);
  gbitmap_destroy(s_res_bat_low);
  gbitmap_destroy(s_res_sunrise);
  gbitmap_destroy(s_res_sunset);
}
// END AUTO-GENERATED UI CODE

int forceSunUpdate = 0;
float latitude = GPS_INVALID;
float longitude = GPS_INVALID;
static time_t accel_lastchange = 0;
static void update_suntime(struct tm *current_time);

static void setDate(struct tm *current_time) {
  static char DateBuffer[] = "00/00/0000"; 
  text_layer_set_text(Day, days[current_time->tm_wday]);
  strftime(DateBuffer, sizeof("00/00/0000"), "%d/%m/%Y", current_time);
  text_layer_set_text(actDate, DateBuffer);
  
  update_suntime(current_time);
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
  if (!hideseconds) {
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
  }
    
  // minute update
  if (tick_time->tm_sec == 0)
    handle_tick(tick_time, MINUTE_UNIT);
  
  if (!hidesunriseset) {
    // forced suncalc update 
    if (forceSunUpdate){
      update_suntime(tick_time);
      update_sunrisesetimage(0);
      forceSunUpdate = 0;
    }
  }

}

void draw_edge(GContext* ctx, uint8_t edgenr, GColor mydrawcolor) {
  graphics_context_set_fill_color(ctx, mydrawcolor);
  gpath_draw_filled(ctx, edge_path[edgenr]);
}

void draw_rect(GContext* ctx, uint8_t from, uint8_t to, GColor mydrawcolor,
	       bool vertical) {
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

void update_sunrisesetimage(uint8_t usestored)
{
  if (usestored) {
    bitmap_layer_set_bitmap(sunrise, s_res_sunrise_stored);
    bitmap_layer_set_bitmap(sunset, s_res_sunset_stored);
  } else {
    bitmap_layer_set_bitmap(sunrise, s_res_sunrise);
    bitmap_layer_set_bitmap(sunset, s_res_sunset);
  }
}

static void update_suntime(struct tm *current_time)
{
  if (latitude == GPS_INVALID || longitude == GPS_INVALID)
    return;
  
  static char sunrise[] = "00:00";
  static char sunset[] = "00:00";
  
  float temp_suncalc = calcsun(longitude, latitude, 0, current_time);
  snprintf(sunrise, sizeof("00:00"),"%02d:%02d",
	   (int)temp_suncalc, (int)(60*(temp_suncalc-((int)(temp_suncalc)))));
  
  temp_suncalc = calcsun(longitude, latitude, 1, current_time);
  snprintf(sunset, sizeof("00:00"), "%02d:%02d",
	   (int)temp_suncalc, (int)(60*(temp_suncalc-((int)(temp_suncalc)))));
  
  text_layer_set_text(sunrisetime, sunrise);
  text_layer_set_text(sunsettime, sunset);
  
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

static void updateUIforConfig()
{
    layer_set_hidden((Layer*)sunrise, !!hidesunriseset);
    layer_set_hidden((Layer*)sunset, !!hidesunriseset);
    layer_set_hidden((Layer*)sunrisetime, !!hidesunriseset);
    layer_set_hidden((Layer*)sunsettime, !!hidesunriseset);  
    
    layer_set_hidden((Layer*)seconds_bottom, !!hideseconds);
    layer_set_hidden((Layer*)seconds_top, !!hideseconds);
    layer_set_hidden((Layer*)seconds_left, !!hideseconds);
    layer_set_hidden((Layer*)seconds_right, !!hideseconds);
}


/* Note to the following code: 
*  Aim is to detect if pebble was not moved and keep time since last movement
*  This is a very simple solution and is error prone.
*  No movement could be detected when there was a short movement between 
*  measurements.
*  For now this is acceptable since we would go in powersafe mode to early.
*  But a simple minimal shake would wake us up.
*
*  This should be replaced with a better solution when avaiable 
*/
static void handle_acceldata(AccelData *data, uint32_t num_samples) { 
  uint8_t i;
  for (i = 1; i < num_samples; ++i) {
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "i: %d -- sample.x: %d, sample.y: %d, sample.z: %d", i, data[i].x, data[i].y, data[i].z);
    if (abs(data[i].x - data[0].x) > 24 || 
        abs(data[i].y - data[0].y) > 24 || 
        abs(data[i].z - data[0].z) > (24*2)) {
      accel_lastchange = time(NULL);
    return;
    }
  }
  
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "time nochange: %ld",time(NULL) - accel_lastchange);
  
}

static void init_data() {
  // load configuration
  updateconfig();
  updateUIforConfig();
  
  time_t now = time(NULL);
  struct tm *current_time;// KEY top get longitude data from dict 
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
  
  latitude = persist_exists(GETLATITUDE) ? 
			persist_read_int(GETLATITUDE)/1000000 : GPS_INVALID;
  longitude = persist_exists(GETLONGITUDE) ? 
			persist_read_int(GETLONGITUDE)/1000000 : GPS_INVALID; 
  
  // first refresh
  handle_tick(current_time, MINUTE_UNIT);  
  setDate(current_time);
  handle_bluetooth(bluetooth_connection_service_peek());
  handle_battery(battery_state_service_peek());
  
  //register events
  bluetooth_connection_service_subscribe(handle_bluetooth);
  accel_data_service_subscribe(15, handle_acceldata);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  accel_lastchange = time(NULL);
  //tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) handle_tick);
  tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) handle_seconds);
  battery_state_service_subscribe(handle_battery);
  
  // custom resources
  s_res_nobluetooth = gbitmap_create_with_resource(RESOURCE_ID_nobluetooth); 
  
   if (!hidesunriseset) {
    // init communication
    app_message_register_inbox_received(inbox_received);
    app_message_open(app_message_inbox_size_maximum(),
		   app_message_outbox_size_maximum());
  
    // refresh position
    get_current_location();
  }

}

static void handle_window_unload(Window* window) {
  bluetooth_connection_service_unsubscribe();
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  accel_data_service_unsubscribe();
  destroy_ui();
  // custom resources
  gbitmap_destroy(s_res_nobluetooth);
  
  app_message_deregister_callbacks();
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