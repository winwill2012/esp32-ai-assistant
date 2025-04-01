# Copyright 2025 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import utime as time
import usys as sys
import lvgl as lv
import ustruct
import fs_driver

lv.init()

# Register display driver.
disp_drv = lv.sdl_window_create(240, 320)
lv.sdl_window_set_resizeable(disp_drv, False)
lv.sdl_window_set_title(disp_drv, "Simulator (MicroPython)")

# Regsiter input driver
mouse = lv.sdl_mouse_create()

# Add default theme for bottom layer
bottom_layer = lv.layer_bottom()
lv.theme_apply(bottom_layer)

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_scale(v)

def anim_img_rotate_cb(obj, v):
    obj.set_rotation(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.binfont_create(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.image_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = lv.calendar.__cast__(e.get_current_target())
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RESULT.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    datetext = lv.label.__cast__(e.get_target())
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = lv.screen_active()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = datetext.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, datetext), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    calendar = lv.calendar.__cast__(e.get_current_target())
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if calendar.get_pressed_date(date) == lv.RESULT.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.remove_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            calendar.delete()

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = lv.textarea.__cast__(e.get_target())
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.remove_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

# Create screen_main
screen_main = lv.obj()
g_kb_screen_main = lv.keyboard(screen_main)
g_kb_screen_main.add_event_cb(lambda e: ta_event_cb(e, g_kb_screen_main), lv.EVENT.ALL, None)
g_kb_screen_main.add_flag(lv.obj.FLAG.HIDDEN)
g_kb_screen_main.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_size(240, 320)
screen_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_container_header
screen_main_container_header = lv.obj(screen_main)
screen_main_container_header.set_pos(0, 0)
screen_main_container_header.set_size(240, 25)
screen_main_container_header.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_container_header, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_container_header.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_radius(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_bg_opa(182, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_container_header.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_main_img_wifi_state
screen_main_img_wifi_state = lv.image(screen_main_container_header)
screen_main_img_wifi_state.set_src(load_image(r"C:\NXP\GUI-Guider-Projects\xiaozhi-ai\generated\MicroPython\wifi_20_20.png"))
screen_main_img_wifi_state.add_flag(lv.obj.FLAG.CLICKABLE)
screen_main_img_wifi_state.set_pivot(50,50)
screen_main_img_wifi_state.set_rotation(0)
screen_main_img_wifi_state.set_pos(214, 2)
screen_main_img_wifi_state.set_size(20, 20)
# Set style for screen_main_img_wifi_state, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_img_wifi_state.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_current_time
screen_main_label_current_time = lv.label(screen_main_container_header)
screen_main_label_current_time.set_text("18:00")
screen_main_label_current_time.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_current_time.set_width(lv.pct(100))
screen_main_label_current_time.set_pos(2, 4)
screen_main_label_current_time.set_size(48, 16)
# Set style for screen_main_label_current_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_current_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_current_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_btn_recording_state
screen_main_btn_recording_state = lv.button(screen_main_container_header)
screen_main_btn_recording_state_label = lv.label(screen_main_btn_recording_state)
screen_main_btn_recording_state_label.set_text("")
screen_main_btn_recording_state_label.set_long_mode(lv.label.LONG.WRAP)
screen_main_btn_recording_state_label.set_width(lv.pct(100))
screen_main_btn_recording_state_label.align(lv.ALIGN.CENTER, 0, 0)
screen_main_btn_recording_state.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_pos(76, 7)
screen_main_btn_recording_state.set_size(10, 10)
# Set style for screen_main_btn_recording_state, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_btn_recording_state.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_bg_color(lv.color_hex(0xcfd1d3), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_btn_recording_state.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_label_global_state
screen_main_label_global_state = lv.label(screen_main_container_header)
screen_main_label_global_state.set_text("正在聆听")
screen_main_label_global_state.set_long_mode(lv.label.LONG.WRAP)
screen_main_label_global_state.set_width(lv.pct(100))
screen_main_label_global_state.set_pos(92, 4)
screen_main_label_global_state.set_size(70, 15)
# Set style for screen_main_label_global_state, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_label_global_state.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_label_global_state.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_main_list_message_history
screen_main_list_message_history = lv.list(screen_main)
screen_main_list_message_history.set_pos(0, 25)
screen_main_list_message_history.set_size(235, 250)
screen_main_list_message_history.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_main_list_message_history, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_list_message_history.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_pad_right(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_pad_bottom(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_main_list_message_history, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_main_list_message_history.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_main_list_message_history.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_main_list_message_history, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_message_history_extra_btns_main_default = lv.style_t()
style_screen_main_list_message_history_extra_btns_main_default.init()
style_screen_main_list_message_history_extra_btns_main_default.set_pad_top(5)
style_screen_main_list_message_history_extra_btns_main_default.set_pad_left(5)
style_screen_main_list_message_history_extra_btns_main_default.set_pad_right(5)
style_screen_main_list_message_history_extra_btns_main_default.set_pad_bottom(5)
style_screen_main_list_message_history_extra_btns_main_default.set_border_width(0)
style_screen_main_list_message_history_extra_btns_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_main_list_message_history_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_main_list_message_history_extra_btns_main_default.set_text_opa(255)
style_screen_main_list_message_history_extra_btns_main_default.set_radius(3)
style_screen_main_list_message_history_extra_btns_main_default.set_bg_opa(255)
style_screen_main_list_message_history_extra_btns_main_default.set_bg_color(lv.color_hex(0xffffff))
style_screen_main_list_message_history_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Set style for screen_main_list_message_history, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_main_list_message_history_extra_texts_main_default = lv.style_t()
style_screen_main_list_message_history_extra_texts_main_default.init()
style_screen_main_list_message_history_extra_texts_main_default.set_pad_top(5)
style_screen_main_list_message_history_extra_texts_main_default.set_pad_left(5)
style_screen_main_list_message_history_extra_texts_main_default.set_pad_right(5)
style_screen_main_list_message_history_extra_texts_main_default.set_pad_bottom(5)
style_screen_main_list_message_history_extra_texts_main_default.set_border_width(0)
style_screen_main_list_message_history_extra_texts_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_main_list_message_history_extra_texts_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_main_list_message_history_extra_texts_main_default.set_text_opa(255)
style_screen_main_list_message_history_extra_texts_main_default.set_radius(3)
style_screen_main_list_message_history_extra_texts_main_default.set_transform_width(0)
style_screen_main_list_message_history_extra_texts_main_default.set_bg_opa(255)
style_screen_main_list_message_history_extra_texts_main_default.set_bg_color(lv.color_hex(0xffffff))
style_screen_main_list_message_history_extra_texts_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Create screen_main_imgbtn_mic
screen_main_imgbtn_mic = lv.imagebutton(screen_main)
screen_main_imgbtn_mic.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_imgbtn_mic.set_src(lv.imagebutton.STATE.RELEASED, load_image(r"C:\NXP\GUI-Guider-Projects\xiaozhi-ai\generated\MicroPython\stop_25_25.png"), None, None)
screen_main_imgbtn_mic.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_imgbtn_mic_label = lv.label(screen_main_imgbtn_mic)
screen_main_imgbtn_mic_label.set_text("")
screen_main_imgbtn_mic_label.set_long_mode(lv.label.LONG.WRAP)
screen_main_imgbtn_mic_label.set_width(lv.pct(100))
screen_main_imgbtn_mic_label.align(lv.ALIGN.CENTER, 0, 0)
screen_main_imgbtn_mic.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_imgbtn_mic.set_pos(107, 286)
screen_main_imgbtn_mic.set_size(25, 25)
# Set style for screen_main_imgbtn_mic, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_main_imgbtn_mic.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_imgbtn_mic.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_imgbtn_mic.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_imgbtn_mic.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_main_imgbtn_mic.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_main_imgbtn_mic, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
screen_main_imgbtn_mic.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_main_imgbtn_mic.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.PRESSED)
screen_main_imgbtn_mic.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.PRESSED)
screen_main_imgbtn_mic.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
screen_main_imgbtn_mic.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
# Set style for screen_main_imgbtn_mic, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
screen_main_imgbtn_mic.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_main_imgbtn_mic.set_style_text_color(lv.color_hex(0xFF33FF), lv.PART.MAIN|lv.STATE.CHECKED)
screen_main_imgbtn_mic.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.CHECKED)
screen_main_imgbtn_mic.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.CHECKED)
screen_main_imgbtn_mic.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for screen_main_imgbtn_mic, Part: lv.PART.MAIN, State: LV_IMAGEBUTTON_STATE_RELEASED.
screen_main_imgbtn_mic.set_style_image_opa(255, lv.PART.MAIN|lv.imagebutton.STATE.RELEASED)

screen_main.update_layout()
# Create screen_settings
screen_settings = lv.obj()
g_kb_screen_settings = lv.keyboard(screen_settings)
g_kb_screen_settings.add_event_cb(lambda e: ta_event_cb(e, g_kb_screen_settings), lv.EVENT.ALL, None)
g_kb_screen_settings.add_flag(lv.obj.FLAG.HIDDEN)
g_kb_screen_settings.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings.set_size(240, 320)
screen_settings.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_settings.add_flag(lv.obj.FLAG.HIDDEN)
# Set style for screen_settings, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_label_settings_title
screen_settings_label_settings_title = lv.label(screen_settings)
screen_settings_label_settings_title.set_text("设置")
screen_settings_label_settings_title.set_long_mode(lv.label.LONG.WRAP)
screen_settings_label_settings_title.set_width(lv.pct(100))
screen_settings_label_settings_title.set_pos(83, 29)
screen_settings_label_settings_title.set_size(72, 18)
# Set style for screen_settings_label_settings_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_label_settings_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_settings_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_btn_networking_setting
screen_settings_btn_networking_setting = lv.button(screen_settings)
screen_settings_btn_networking_setting_label = lv.label(screen_settings_btn_networking_setting)
screen_settings_btn_networking_setting_label.set_text(""+lv.SYMBOL.WIFI+" WiFi设置")
screen_settings_btn_networking_setting_label.set_long_mode(lv.label.LONG.WRAP)
screen_settings_btn_networking_setting_label.set_width(lv.pct(100))
screen_settings_btn_networking_setting_label.align(lv.ALIGN.CENTER, 0, 0)
screen_settings_btn_networking_setting.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_pos(23, 69)
screen_settings_btn_networking_setting.set_size(194, 45)
# Set style for screen_settings_btn_networking_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_btn_networking_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_bg_grad_color(lv.color_hex(0x93acc1), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_bg_main_stop(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_bg_grad_stop(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_networking_setting.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_btn_system_setting
screen_settings_btn_system_setting = lv.button(screen_settings)
screen_settings_btn_system_setting_label = lv.label(screen_settings_btn_system_setting)
screen_settings_btn_system_setting_label.set_text(""+lv.SYMBOL.SETTINGS+" 系统设置")
screen_settings_btn_system_setting_label.set_long_mode(lv.label.LONG.WRAP)
screen_settings_btn_system_setting_label.set_width(lv.pct(100))
screen_settings_btn_system_setting_label.align(lv.ALIGN.CENTER, 0, 0)
screen_settings_btn_system_setting.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_pos(23, 147)
screen_settings_btn_system_setting.set_size(194, 45)
# Set style for screen_settings_btn_system_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_btn_system_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_bg_color(lv.color_hex(0x91b0c9), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_bg_grad_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_bg_main_stop(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_bg_grad_stop(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_system_setting.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_btn_reset_setting
screen_settings_btn_reset_setting = lv.button(screen_settings)
screen_settings_btn_reset_setting_label = lv.label(screen_settings_btn_reset_setting)
screen_settings_btn_reset_setting_label.set_text(""+lv.SYMBOL.REFRESH+" 恢复出厂设置")
screen_settings_btn_reset_setting_label.set_long_mode(lv.label.LONG.WRAP)
screen_settings_btn_reset_setting_label.set_width(lv.pct(100))
screen_settings_btn_reset_setting_label.align(lv.ALIGN.CENTER, 0, 0)
screen_settings_btn_reset_setting.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_pos(23, 225)
screen_settings_btn_reset_setting.set_size(194, 45)
# Set style for screen_settings_btn_reset_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_btn_reset_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_bg_grad_dir(lv.GRAD_DIR.HOR, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_bg_grad_color(lv.color_hex(0xfdb9c3), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_bg_main_stop(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_bg_grad_stop(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_reset_setting.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_cont_1
screen_settings_cont_1 = lv.obj(screen_settings)
screen_settings_cont_1.set_pos(5, 127)
screen_settings_cont_1.set_size(230, 66)
screen_settings_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_settings_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_settings_label_1
screen_settings_label_1 = lv.label(screen_settings_cont_1)
screen_settings_label_1.set_text(""+lv.SYMBOL.BELL+" 恢复出厂设置成功 ")
screen_settings_label_1.set_long_mode(lv.label.LONG.WRAP)
screen_settings_label_1.set_width(lv.pct(100))
screen_settings_label_1.set_pos(4, 7)
screen_settings_label_1.set_size(220, 15)
# Set style for screen_settings_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_settings_btn_1
screen_settings_btn_1 = lv.button(screen_settings_cont_1)
screen_settings_btn_1_label = lv.label(screen_settings_btn_1)
screen_settings_btn_1_label.set_text("确定")
screen_settings_btn_1_label.set_long_mode(lv.label.LONG.WRAP)
screen_settings_btn_1_label.set_width(lv.pct(100))
screen_settings_btn_1_label.align(lv.ALIGN.CENTER, 0, 0)
screen_settings_btn_1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_settings_btn_1.set_pos(2, 36)
screen_settings_btn_1.set_size(222, 20)
# Set style for screen_settings_btn_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_settings_btn_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_bg_color(lv.color_hex(0x26B08C), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_settings_btn_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_settings.update_layout()
# Create screen_networking_setting
screen_networking_setting = lv.obj()
g_kb_screen_networking_setting = lv.keyboard(screen_networking_setting)
g_kb_screen_networking_setting.add_event_cb(lambda e: ta_event_cb(e, g_kb_screen_networking_setting), lv.EVENT.ALL, None)
g_kb_screen_networking_setting.add_flag(lv.obj.FLAG.HIDDEN)
g_kb_screen_networking_setting.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting.set_size(240, 320)
screen_networking_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_networking_setting.add_flag(lv.obj.FLAG.HIDDEN)
# Set style for screen_networking_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_label_networking_setting_title
screen_networking_setting_label_networking_setting_title = lv.label(screen_networking_setting)
screen_networking_setting_label_networking_setting_title.set_text(""+lv.SYMBOL.WIFI+" WiFi设置 ")
screen_networking_setting_label_networking_setting_title.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_label_networking_setting_title.set_width(lv.pct(100))
screen_networking_setting_label_networking_setting_title.set_pos(32, 30)
screen_networking_setting_label_networking_setting_title.set_size(109, 18)
# Set style for screen_networking_setting_label_networking_setting_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_label_networking_setting_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_networking_setting_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_list_wlan
screen_networking_setting_list_wlan = lv.list(screen_networking_setting)
screen_networking_setting_list_wlan.set_pos(5, 96)
screen_networking_setting_list_wlan.set_size(230, 214)
screen_networking_setting_list_wlan.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_networking_setting_list_wlan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_list_wlan.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_pad_right(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_pad_bottom(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_networking_setting_list_wlan, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_networking_setting_list_wlan.set_style_radius(3, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_list_wlan.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
# Set style for screen_networking_setting_list_wlan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_networking_setting_list_wlan_extra_btns_main_default = lv.style_t()
style_screen_networking_setting_list_wlan_extra_btns_main_default.init()
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_pad_top(5)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_pad_left(5)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_pad_right(5)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_pad_bottom(5)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_border_width(0)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_text_opa(255)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_radius(3)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_bg_opa(255)
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_bg_color(lv.color_hex(0xffffff))
style_screen_networking_setting_list_wlan_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Set style for screen_networking_setting_list_wlan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_networking_setting_list_wlan_extra_texts_main_default = lv.style_t()
style_screen_networking_setting_list_wlan_extra_texts_main_default.init()
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_pad_top(5)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_pad_left(5)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_pad_right(5)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_pad_bottom(5)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_border_width(0)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_text_color(lv.color_hex(0x0D3055))
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_text_opa(255)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_radius(3)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_transform_width(0)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_bg_opa(255)
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_bg_color(lv.color_hex(0xffffff))
style_screen_networking_setting_list_wlan_extra_texts_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)

# Create screen_networking_setting_label_tips
screen_networking_setting_label_tips = lv.label(screen_networking_setting)
screen_networking_setting_label_tips.set_text("连接附近的WLAN")
screen_networking_setting_label_tips.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_label_tips.set_width(lv.pct(100))
screen_networking_setting_label_tips.set_pos(9, 71)
screen_networking_setting_label_tips.set_size(120, 15)
# Set style for screen_networking_setting_label_tips, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_label_tips.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_tips.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_btn_refresh
screen_networking_setting_btn_refresh = lv.button(screen_networking_setting)
screen_networking_setting_btn_refresh_label = lv.label(screen_networking_setting_btn_refresh)
screen_networking_setting_btn_refresh_label.set_text(""+lv.SYMBOL.REFRESH+"")
screen_networking_setting_btn_refresh_label.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_btn_refresh_label.set_width(lv.pct(100))
screen_networking_setting_btn_refresh_label.align(lv.ALIGN.CENTER, 0, 0)
screen_networking_setting_btn_refresh.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_pos(163, 68)
screen_networking_setting_btn_refresh.set_size(20, 20)
# Set style for screen_networking_setting_btn_refresh, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_btn_refresh.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_refresh.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_btn_back
screen_networking_setting_btn_back = lv.button(screen_networking_setting)
screen_networking_setting_btn_back_label = lv.label(screen_networking_setting_btn_back)
screen_networking_setting_btn_back_label.set_text(""+lv.SYMBOL.LEFT+" ")
screen_networking_setting_btn_back_label.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_btn_back_label.set_width(lv.pct(100))
screen_networking_setting_btn_back_label.align(lv.ALIGN.CENTER, 0, 0)
screen_networking_setting_btn_back.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_pos(8, 30)
screen_networking_setting_btn_back.set_size(20, 20)
# Set style for screen_networking_setting_btn_back, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_btn_back.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_back.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_cont_mask
screen_networking_setting_cont_mask = lv.obj(screen_networking_setting)
screen_networking_setting_cont_mask.set_pos(0, 0)
screen_networking_setting_cont_mask.set_size(240, 320)
screen_networking_setting_cont_mask.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_networking_setting_cont_mask, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_cont_mask.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_mask.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_cont_wifi_password_dialog
screen_networking_setting_cont_wifi_password_dialog = lv.obj(screen_networking_setting)
screen_networking_setting_cont_wifi_password_dialog.set_pos(5, 60)
screen_networking_setting_cont_wifi_password_dialog.set_size(230, 102)
screen_networking_setting_cont_wifi_password_dialog.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_networking_setting_cont_wifi_password_dialog, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_cont_wifi_password_dialog.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_cont_wifi_password_dialog.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_networking_setting_btn_cancel
screen_networking_setting_btn_cancel = lv.button(screen_networking_setting_cont_wifi_password_dialog)
screen_networking_setting_btn_cancel_label = lv.label(screen_networking_setting_btn_cancel)
screen_networking_setting_btn_cancel_label.set_text("取消")
screen_networking_setting_btn_cancel_label.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_btn_cancel_label.set_width(lv.pct(100))
screen_networking_setting_btn_cancel_label.align(lv.ALIGN.CENTER, 0, 0)
screen_networking_setting_btn_cancel.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_pos(123, 64)
screen_networking_setting_btn_cancel.set_size(100, 30)
# Set style for screen_networking_setting_btn_cancel, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_btn_cancel.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_bg_color(lv.color_hex(0xff0027), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_cancel.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_btn_confirm
screen_networking_setting_btn_confirm = lv.button(screen_networking_setting_cont_wifi_password_dialog)
screen_networking_setting_btn_confirm_label = lv.label(screen_networking_setting_btn_confirm)
screen_networking_setting_btn_confirm_label.set_text("连接")
screen_networking_setting_btn_confirm_label.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_btn_confirm_label.set_width(lv.pct(100))
screen_networking_setting_btn_confirm_label.align(lv.ALIGN.CENTER, 0, 0)
screen_networking_setting_btn_confirm.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_pos(4, 64)
screen_networking_setting_btn_confirm.set_size(100, 30)
# Set style for screen_networking_setting_btn_confirm, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_btn_confirm.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_bg_color(lv.color_hex(0x26B08C), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_btn_confirm.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_label_title
screen_networking_setting_label_title = lv.label(screen_networking_setting_cont_wifi_password_dialog)
screen_networking_setting_label_title.set_text("请输入WiFi密码")
screen_networking_setting_label_title.set_long_mode(lv.label.LONG.WRAP)
screen_networking_setting_label_title.set_width(lv.pct(100))
screen_networking_setting_label_title.set_pos(4, 6)
screen_networking_setting_label_title.set_size(219, 15)
# Set style for screen_networking_setting_label_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_label_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_label_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_networking_setting_ta_wifi_password
screen_networking_setting_ta_wifi_password = lv.textarea(screen_networking_setting_cont_wifi_password_dialog)
screen_networking_setting_ta_wifi_password.set_text("")
screen_networking_setting_ta_wifi_password.set_placeholder_text("")
screen_networking_setting_ta_wifi_password.set_password_bullet("*")
screen_networking_setting_ta_wifi_password.set_password_mode(True)
screen_networking_setting_ta_wifi_password.set_one_line(True)
screen_networking_setting_ta_wifi_password.set_accepted_chars("")
screen_networking_setting_ta_wifi_password.set_max_length(32)
screen_networking_setting_ta_wifi_password.add_event_cb(lambda e: ta_event_cb(e, g_kb_screen_networking_setting), lv.EVENT.ALL, None)
screen_networking_setting_ta_wifi_password.set_pos(0, 28)
screen_networking_setting_ta_wifi_password.set_size(226, 30)
# Set style for screen_networking_setting_ta_wifi_password, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_networking_setting_ta_wifi_password.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_border_color(lv.color_hex(0xe6e6e6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_pad_top(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_pad_right(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_pad_left(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_radius(4, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_networking_setting_ta_wifi_password, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
screen_networking_setting_ta_wifi_password.set_style_bg_opa(255, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)
screen_networking_setting_ta_wifi_password.set_style_radius(0, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

screen_networking_setting.update_layout()
# Create screen_system_setting
screen_system_setting = lv.obj()
g_kb_screen_system_setting = lv.keyboard(screen_system_setting)
g_kb_screen_system_setting.add_event_cb(lambda e: ta_event_cb(e, g_kb_screen_system_setting), lv.EVENT.ALL, None)
g_kb_screen_system_setting.add_flag(lv.obj.FLAG.HIDDEN)
g_kb_screen_system_setting.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting.set_size(240, 320)
screen_system_setting.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_system_setting, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_label_speaker_setting_title
screen_system_setting_label_speaker_setting_title = lv.label(screen_system_setting)
screen_system_setting_label_speaker_setting_title.set_text(" "+lv.SYMBOL.SETTINGS+" 系统设置")
screen_system_setting_label_speaker_setting_title.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_speaker_setting_title.set_width(lv.pct(100))
screen_system_setting_label_speaker_setting_title.set_pos(32, 30)
screen_system_setting_label_speaker_setting_title.set_size(109, 18)
# Set style for screen_system_setting_label_speaker_setting_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_speaker_setting_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speaker_setting_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_label_speak_volume
screen_system_setting_label_speak_volume = lv.label(screen_system_setting)
screen_system_setting_label_speak_volume.set_text("音         量")
screen_system_setting_label_speak_volume.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_speak_volume.set_width(lv.pct(100))
screen_system_setting_label_speak_volume.set_pos(6, 102)
screen_system_setting_label_speak_volume.set_size(60, 14)
# Set style for screen_system_setting_label_speak_volume, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_speak_volume.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_volume.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_slider_speak_volume
screen_system_setting_slider_speak_volume = lv.slider(screen_system_setting)
screen_system_setting_slider_speak_volume.set_range(0, 100)
screen_system_setting_slider_speak_volume.set_mode(lv.slider.MODE.NORMAL)
screen_system_setting_slider_speak_volume.set_value(50, lv.ANIM.OFF)
screen_system_setting_slider_speak_volume.set_pos(73, 105)
screen_system_setting_slider_speak_volume.set_size(160, 5)
# Set style for screen_system_setting_slider_speak_volume, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_slider_speak_volume.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_system_setting_slider_speak_volume, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_system_setting_slider_speak_volume.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_system_setting_slider_speak_volume, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_system_setting_slider_speak_volume.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_speak_volume.set_style_radius(50, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create screen_system_setting_label_speak_speed
screen_system_setting_label_speak_speed = lv.label(screen_system_setting)
screen_system_setting_label_speak_speed.set_text("语         速")
screen_system_setting_label_speak_speed.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_speak_speed.set_width(lv.pct(100))
screen_system_setting_label_speak_speed.set_pos(6, 145)
screen_system_setting_label_speak_speed.set_size(60, 14)
# Set style for screen_system_setting_label_speak_speed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_speak_speed.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_speak_speed.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_spinbox_speak_speed
screen_system_setting_spinbox_speak_speed = lv.spinbox(screen_system_setting)
screen_system_setting_spinbox_speak_speed.set_width(102)
screen_system_setting_spinbox_speak_speed.set_height(24)
screen_system_setting_spinbox_speak_speed.set_digit_format(2, 1)
screen_system_setting_spinbox_speak_speed.set_range(-99, 99)
screen_system_setting_spinbox_speak_speed_height = screen_system_setting_spinbox_speak_speed.get_height()
screen_system_setting_spinbox_speak_speed_btn_plus = lv.button(screen_system_setting)
screen_system_setting_spinbox_speak_speed_btn_plus.set_size(screen_system_setting_spinbox_speak_speed_height, screen_system_setting_spinbox_speak_speed_height)
screen_system_setting_spinbox_speak_speed_btn_plus.set_style_bg_image_src(lv.SYMBOL.PLUS, 0)
screen_system_setting_spinbox_speak_speed_btn_plus.add_event_cb(lambda e: spinbox_increment_event_cb(e, screen_system_setting_spinbox_speak_speed), lv.EVENT.ALL, None)
screen_system_setting_spinbox_speak_speed_btn_minus = lv.button(screen_system_setting)
screen_system_setting_spinbox_speak_speed_btn_minus.set_size(screen_system_setting_spinbox_speak_speed_height, screen_system_setting_spinbox_speak_speed_height)
screen_system_setting_spinbox_speak_speed_btn_minus.set_style_bg_image_src(lv.SYMBOL.MINUS, 0)
screen_system_setting_spinbox_speak_speed_btn_minus.add_event_cb(lambda e: spinbox_decrement_event_cb(e, screen_system_setting_spinbox_speak_speed), lv.EVENT.ALL, None)
screen_system_setting_spinbox_speak_speed.set_pos(102, 140)
screen_system_setting_spinbox_speak_speed_btn_plus.align_to(screen_system_setting_spinbox_speak_speed, lv.ALIGN.OUT_RIGHT_MID, 5, 0)
screen_system_setting_spinbox_speak_speed_btn_minus.align_to(screen_system_setting_spinbox_speak_speed, lv.ALIGN.OUT_LEFT_MID, -5, 0)
# Set style for screen_system_setting_spinbox_speak_speed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_spinbox_speak_speed.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_pad_right(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_pad_left(20, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_system_setting_spinbox_speak_speed, Part: lv.PART.CURSOR, State: lv.STATE.DEFAULT.
screen_system_setting_spinbox_speak_speed.set_style_text_color(lv.color_hex(0xffffff), lv.PART.CURSOR|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_font(test_font("montserratMedium", 12), lv.PART.CURSOR|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_text_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_bg_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.CURSOR|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.CURSOR|lv.STATE.DEFAULT)
# Set style for screen_system_setting_spinbox_speak_speed, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default = lv.style_t()
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.init()
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_text_opa(255)
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_bg_opa(255)
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_bg_color(lv.color_hex(0x2195f6))
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_border_width(0)
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_radius(5)
style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default.set_shadow_width(0)
screen_system_setting_spinbox_speak_speed_btn_plus.add_style(style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_spinbox_speak_speed_btn_minus.add_style(style_screen_system_setting_spinbox_speak_speed_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_label_voice_type
screen_system_setting_label_voice_type = lv.label(screen_system_setting)
screen_system_setting_label_voice_type.set_text("音         色")
screen_system_setting_label_voice_type.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_voice_type.set_width(lv.pct(100))
screen_system_setting_label_voice_type.set_pos(6, 188)
screen_system_setting_label_voice_type.set_size(60, 14)
# Set style for screen_system_setting_label_voice_type, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_voice_type.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_voice_type.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_ddlist_voice_type
screen_system_setting_ddlist_voice_type = lv.dropdown(screen_system_setting)
screen_system_setting_ddlist_voice_type.set_options("")
screen_system_setting_ddlist_voice_type.set_pos(73, 182)
screen_system_setting_ddlist_voice_type.set_size(160, 25)
# Set style for screen_system_setting_ddlist_voice_type, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_voice_type.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_system_setting_ddlist_voice_type, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked = lv.style_t()
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.init()
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_border_width(1)
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_border_opa(255)
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_border_side(lv.BORDER_SIDE.FULL)
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_radius(3)
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_bg_opa(255)
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_voice_type.get_list().add_style(style_screen_system_setting_ddlist_voice_type_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for screen_system_setting_ddlist_voice_type, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_voice_type.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_voice_type.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_system_setting_ddlist_voice_type, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default = lv.style_t()
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default.init()
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default.set_radius(3)
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default.set_bg_opa(255)
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_voice_type.get_list().add_style(style_screen_system_setting_ddlist_voice_type_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_system_setting_ddlist_persona
screen_system_setting_ddlist_persona = lv.dropdown(screen_system_setting)
screen_system_setting_ddlist_persona.set_options("")
screen_system_setting_ddlist_persona.set_pos(73, 225)
screen_system_setting_ddlist_persona.set_size(160, 25)
# Set style for screen_system_setting_ddlist_persona, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_persona.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_system_setting_ddlist_persona, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_screen_system_setting_ddlist_persona_extra_list_selected_checked = lv.style_t()
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.init()
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_border_width(1)
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_border_opa(255)
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_border_side(lv.BORDER_SIDE.FULL)
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_radius(3)
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_bg_opa(255)
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
style_screen_system_setting_ddlist_persona_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_persona.get_list().add_style(style_screen_system_setting_ddlist_persona_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for screen_system_setting_ddlist_persona, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_persona.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_persona.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_system_setting_ddlist_persona, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default = lv.style_t()
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default.init()
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default.set_radius(3)
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default.set_bg_opa(255)
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_persona.get_list().add_style(style_screen_system_setting_ddlist_persona_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_system_setting_ddlist_environment_noise
screen_system_setting_ddlist_environment_noise = lv.dropdown(screen_system_setting)
screen_system_setting_ddlist_environment_noise.set_options("")
screen_system_setting_ddlist_environment_noise.set_pos(73, 268)
screen_system_setting_ddlist_environment_noise.set_size(160, 25)
# Set style for screen_system_setting_ddlist_environment_noise, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_environment_noise.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_system_setting_ddlist_environment_noise, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked = lv.style_t()
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.init()
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_border_width(1)
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_border_opa(255)
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_border_side(lv.BORDER_SIDE.FULL)
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_radius(3)
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_bg_opa(255)
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_environment_noise.get_list().add_style(style_screen_system_setting_ddlist_environment_noise_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for screen_system_setting_ddlist_environment_noise, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_ddlist_environment_noise.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_text_font(test_font("Siyuan_Regular", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_color(lv.color_hex(0xe1e6ee), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_ddlist_environment_noise.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_system_setting_ddlist_environment_noise, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default = lv.style_t()
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default.init()
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default.set_radius(3)
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default.set_bg_opa(255)
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
screen_system_setting_ddlist_environment_noise.get_list().add_style(style_screen_system_setting_ddlist_environment_noise_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create screen_system_setting_label_persona
screen_system_setting_label_persona = lv.label(screen_system_setting)
screen_system_setting_label_persona.set_text("人         设")
screen_system_setting_label_persona.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_persona.set_width(lv.pct(100))
screen_system_setting_label_persona.set_pos(6, 231)
screen_system_setting_label_persona.set_size(60, 14)
# Set style for screen_system_setting_label_persona, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_persona.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_persona.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_label_environment_noise
screen_system_setting_label_environment_noise = lv.label(screen_system_setting)
screen_system_setting_label_environment_noise.set_text("环境噪音")
screen_system_setting_label_environment_noise.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_environment_noise.set_width(lv.pct(100))
screen_system_setting_label_environment_noise.set_pos(6, 274)
screen_system_setting_label_environment_noise.set_size(60, 14)
# Set style for screen_system_setting_label_environment_noise, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_environment_noise.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_environment_noise.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_slider_screen_brightness
screen_system_setting_slider_screen_brightness = lv.slider(screen_system_setting)
screen_system_setting_slider_screen_brightness.set_range(0, 100)
screen_system_setting_slider_screen_brightness.set_mode(lv.slider.MODE.NORMAL)
screen_system_setting_slider_screen_brightness.set_value(50, lv.ANIM.OFF)
screen_system_setting_slider_screen_brightness.set_pos(73, 63)
screen_system_setting_slider_screen_brightness.set_size(160, 5)
# Set style for screen_system_setting_slider_screen_brightness, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_slider_screen_brightness.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_radius(50, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for screen_system_setting_slider_screen_brightness, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_system_setting_slider_screen_brightness.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_radius(50, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_system_setting_slider_screen_brightness, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_system_setting_slider_screen_brightness.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_system_setting_slider_screen_brightness.set_style_radius(50, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create screen_system_setting_label_screen_brightness
screen_system_setting_label_screen_brightness = lv.label(screen_system_setting)
screen_system_setting_label_screen_brightness.set_text("屏幕亮度")
screen_system_setting_label_screen_brightness.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_label_screen_brightness.set_width(lv.pct(100))
screen_system_setting_label_screen_brightness.set_pos(6, 58)
screen_system_setting_label_screen_brightness.set_size(60, 14)
# Set style for screen_system_setting_label_screen_brightness, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_label_screen_brightness.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_font(test_font("Siyuan_yuanti", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_label_screen_brightness.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_system_setting_btn_back
screen_system_setting_btn_back = lv.button(screen_system_setting)
screen_system_setting_btn_back_label = lv.label(screen_system_setting_btn_back)
screen_system_setting_btn_back_label.set_text(""+lv.SYMBOL.LEFT+" ")
screen_system_setting_btn_back_label.set_long_mode(lv.label.LONG.WRAP)
screen_system_setting_btn_back_label.set_width(lv.pct(100))
screen_system_setting_btn_back_label.align(lv.ALIGN.CENTER, 0, 0)
screen_system_setting_btn_back.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_pos(8, 30)
screen_system_setting_btn_back.set_size(20, 20)
# Set style for screen_system_setting_btn_back, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_system_setting_btn_back.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_text_font(test_font("Siyuan_Heiti", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_system_setting_btn_back.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_system_setting.update_layout()

def screen_main_event_handler(e):
    code = e.get_code()
    indev = lv.indev_active()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.LEFT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.screen_load_anim(screen_settings, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)
screen_main.add_event_cb(lambda e: screen_main_event_handler(e), lv.EVENT.ALL, None)

def screen_main_imgbtn_mic_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

screen_main_imgbtn_mic.add_event_cb(lambda e: screen_main_imgbtn_mic_event_handler(e), lv.EVENT.ALL, None)

def screen_settings_event_handler(e):
    code = e.get_code()
    indev = lv.indev_active()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.RIGHT == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        lv.screen_load_anim(screen_main, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)
screen_settings.add_event_cb(lambda e: screen_settings_event_handler(e), lv.EVENT.ALL, None)

def screen_settings_btn_networking_setting_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.screen_load_anim(screen_networking_setting, lv.SCR_LOAD_ANIM.MOVE_LEFT, 200, 200, False)
screen_settings_btn_networking_setting.add_event_cb(lambda e: screen_settings_btn_networking_setting_event_handler(e), lv.EVENT.ALL, None)

def screen_settings_btn_system_setting_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.screen_load_anim(screen_system_setting, lv.SCR_LOAD_ANIM.MOVE_LEFT, 200, 200, False)
screen_settings_btn_system_setting.add_event_cb(lambda e: screen_settings_btn_system_setting_event_handler(e), lv.EVENT.ALL, None)

def screen_settings_btn_reset_setting_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

screen_settings_btn_reset_setting.add_event_cb(lambda e: screen_settings_btn_reset_setting_event_handler(e), lv.EVENT.ALL, None)

def screen_networking_setting_btn_refresh_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        

screen_networking_setting_btn_refresh.add_event_cb(lambda e: screen_networking_setting_btn_refresh_event_handler(e), lv.EVENT.ALL, None)

def screen_networking_setting_btn_back_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.screen_load_anim(screen_settings, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)
screen_networking_setting_btn_back.add_event_cb(lambda e: screen_networking_setting_btn_back_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_slider_speak_volume_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_system_setting_slider_speak_volume.add_event_cb(lambda e: screen_system_setting_slider_speak_volume_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_ddlist_voice_type_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_system_setting_ddlist_voice_type.add_event_cb(lambda e: screen_system_setting_ddlist_voice_type_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_ddlist_persona_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_system_setting_ddlist_persona.add_event_cb(lambda e: screen_system_setting_ddlist_persona_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_ddlist_environment_noise_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_system_setting_ddlist_environment_noise.add_event_cb(lambda e: screen_system_setting_ddlist_environment_noise_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_slider_screen_brightness_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.VALUE_CHANGED):
        pass
        

screen_system_setting_slider_screen_brightness.add_event_cb(lambda e: screen_system_setting_slider_screen_brightness_event_handler(e), lv.EVENT.ALL, None)

def screen_system_setting_btn_back_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.screen_load_anim(screen_settings, lv.SCR_LOAD_ANIM.MOVE_RIGHT, 200, 200, False)
screen_system_setting_btn_back.add_event_cb(lambda e: screen_system_setting_btn_back_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.screen_load(screen_settings)

if __name__ == '__main__':
    while True:
        lv.task_handler()
        time.sleep_ms(5)
