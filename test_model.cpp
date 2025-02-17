#include <kernels/ncnn-meta/kernels.h>
#include <model.h>

#include <gtest/gtest.h>

// TODO: generate models
TEST(Model, cuda_fp16) {
  const std::string model_dir(std::getenv("FR_MODEL_DIR"));
  rwkv::Model model(model_dir + "/rwkv-4-0.1b-fp16.fr", "cuda fp16");
  auto output = rwkv::Copy(model.Run(0), rwkv::Device::kCPU);
  auto output_ptr = output.data_ptr<float>();
  EXPECT_FLOAT_EQ(output_ptr[0], -0.19592285);
  EXPECT_FLOAT_EQ(output_ptr[9], -10.234375);
  output = rwkv::Copy(model.Run(0), rwkv::Device::kCPU);
  output_ptr = output.data_ptr<float>();
  EXPECT_FLOAT_EQ(output_ptr[0], -1.5488281);
  EXPECT_FLOAT_EQ(output_ptr[9], -9.640625);
}

TEST(Model, ncnn_fp16) {
  const std::string model_dir(std::getenv("FR_MODEL_DIR"));
  rwkv::ncnnmeta::ExportModel(model_dir + "/rwkv-4-0.1b-fp32.fr",
                              "/tmp/rwkv-4-0.1b-ncnn");
  rwkv::Model model("/tmp/rwkv-4-0.1b-ncnn", "ncnn fp16");
  auto output = rwkv::Copy(model.Run(0), rwkv::Device::kCPU);
  auto output_ptr = output.data_ptr<float>();
  EXPECT_FLOAT_EQ(output_ptr[0], -0.056640625);
  EXPECT_FLOAT_EQ(output_ptr[9], -9.875);
  output = rwkv::Copy(model.Run(0), rwkv::Device::kCPU);
  output_ptr = output.data_ptr<float>();
  EXPECT_FLOAT_EQ(output_ptr[0], -1.28125);
  EXPECT_FLOAT_EQ(output_ptr[9], -9.25);
}
