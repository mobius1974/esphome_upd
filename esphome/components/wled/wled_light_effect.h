#pragma once

#ifdef USE_ARDUINO

#include "esphome/core/component.h"
#include "esphome/components/light/addressable_light_effect.h"

#include <vector>
#include <memory>

class UDP;

namespace esphome {
namespace wled {

class WLEDLightEffect : public light::AddressableLightEffect {
 public:
  WLEDLightEffect(const std::string &name);

  void start() override;
  void stop() override;
  void apply(light::AddressableLight &it, const Color &current_color) override;
  void set_port(uint16_t port) { this->port_ = port; }
  void set_sync_group_mask(uint8_t mask) { this->sync_group_mask_ = mask; }
  void set_blank_on_start(bool blank) { this->blank_on_start_ = blank; }

 protected:
  void blank_all_leds_(light::AddressableLight &it);
  bool parse_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);
  bool parse_notifier_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);
  bool parse_warls_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);
  bool parse_drgb_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);
  bool parse_drgbw_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);
  bool parse_dnrgb_frame_(light::AddressableLight &it, const uint8_t *payload, uint16_t size);

  uint16_t port_{0};
  std::unique_ptr<UDP> udp_;
  uint32_t blank_at_{0};
  uint32_t dropped_{0};
  uint8_t sync_group_mask_{0};
  bool blank_on_start_{true};
};

}  // namespace wled
}  // namespace esphome

#endif  // USE_ARDUINO
