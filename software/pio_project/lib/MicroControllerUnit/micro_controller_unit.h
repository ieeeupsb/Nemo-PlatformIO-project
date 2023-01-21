#pragma once

#include "driver_controller.h"
#include "encoder_reader.h"

class MicroControllerUnit {
  public:
    static MicroControllerUnit &getInstance() {
        static MicroControllerUnit instance;
        return instance;
    }

    void updateEncoders() {
        left_encoder_reader_.Update(void);
        right_encoder_reader_.Update(void);
    }

  private:
    MicroControllerUnit() {}
    MicroControllerUnit(const MicroControllerUnit &) = delete;
    MicroControllerUnit &operator=(const MicroControllerUnit &) = delete;

    EncoderReader left_encoder_reader_;
    EncoderReader right_encoder_reader_;
};
