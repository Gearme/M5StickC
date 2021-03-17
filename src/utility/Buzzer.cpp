#include "Buzzer.h"
#ifdef BUZZER
Buzzer::Buzzer(void)
{
  _volume = 8;
  _begun = false;
}

void Buzzer::begin()
{
  _begun = true;
  ledcSetup(BUZZER_TONE_PIN, 0, 13);
  ledcAttachPin(BUZZER_ENABLE_PIN, BUZZER_TONE_PIN);
  setBeep(4000, 100);
}

void Buzzer::end()
{
  mute();
  ledcDetachPin(BUZZER_ENABLE_PIN);
  _begun = false;
}

void Buzzer::tone(uint16_t frequency)
{
  if (!_begun)
    begin();
  ledcWriteTone(BUZZER_TONE_PIN, frequency);
}

void Buzzer::tone(uint16_t frequency, uint32_t duration)
{
  tone(frequency);
  _count = millis() + duration;
  buzzer_on = 1;
}

void Buzzer::beep()
{
  if (!_begun)
    begin();
  tone(_beep_freq, _beep_duration);
}

void Buzzer::setBeep(uint16_t frequency, uint16_t duration)
{
  _beep_freq = frequency;
  _beep_duration = duration;
}

void Buzzer::setVolume(uint8_t volume)
{
  _volume = 11 - volume;
}

void Buzzer::mute()
{
  ledcWriteTone(BUZZER_TONE_PIN, 0);
  digitalWrite(BUZZER_ENABLE_PIN, 0);
}

void Buzzer::update()
{
  if (buzzer_on)
  {
    if (millis() > _count)
    {
      buzzer_on = 0;
      mute();
    }
  }
}

void Buzzer::write(uint8_t value)
{
  dacWrite(BUZZER_ENABLE_PIN, value);
}

void Buzzer::playMusic(const uint8_t *music_data, uint16_t sample_rate)
{
  uint32_t length = strlen((char *)music_data);
  uint16_t delay_interval = ((uint32_t)1000000 / sample_rate);
  if (_volume != 11)
  {
    for (int i = 0; i < length; i++)
    {
      dacWrite(BUZZER_ENABLE_PIN, music_data[i] / _volume);
      delayMicroseconds(delay_interval);
    }

    for (int t = music_data[length - 1] / _volume; t >= 0; t--)
    {
      dacWrite(BUZZER_ENABLE_PIN, t);
      delay(2);
    }
  }
  // ledcSetup(BUZZER_TONE_PIN, 0, 13);
  ledcAttachPin(BUZZER_ENABLE_PIN, BUZZER_TONE_PIN);
}
#endif