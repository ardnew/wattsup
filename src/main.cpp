#include <cstdlib>
#include <lvglue.hpp>

using adapter_t = glue::adapter<
	glue::timer,
	glue::native::display<glue::native::spi<>, 240, 320>,
 	glue::input
>;

void setup() {
	adapter_t::init(
		[](void) {
			adapter_t::timer_t::init();
		},
		[](void) {
			adapter_t::display_t::init();
		},
		[](void) {
			adapter_t::input_t::init(
				[](lv_indev_t * indev, lv_indev_data_t * data) {

				});
		});
}

void loop() {}
