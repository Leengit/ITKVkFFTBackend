/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkVkForwardFFTImageFilter_h
#define itkVkForwardFFTImageFilter_h

#include "itkForwardFFTImageFilter.h"
#include "itkVkCommon.h"

namespace itk
{
/**
 *\class VkForwardFFTImageFilter
 *
 * \brief Vk-based forward Fast Fourier Transform.
 *
 * This filter computes the forward Fourier transform of an image. The
 * implementation is based on the VkFFT library.
 *
 * This filter is multithreaded and supports input images with sizes which are
 * divisible by primes up to 13.
 *
 * \ingroup FourierTransform
 * \ingroup MultiThreaded
 * \ingroup ITKFFT
 * \ingroup VkFFTBackend
 *
 * \sa VkGlobalConfiguration
 * \sa ForwardFFTImageFilter
 */
template <typename TInputImage>
class VkForwardFFTImageFilter
  : public ForwardFFTImageFilter<TInputImage,
                                 Image<std::complex<typename TInputImage::PixelType>, TInputImage::ImageDimension>>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(VkForwardFFTImageFilter);

  using InputImageType = TInputImage;
  using OutputImageType = Image<std::complex<typename TInputImage::PixelType>, TInputImage::ImageDimension>;

  /** Standard class type aliases. */
  using Self = VkForwardFFTImageFilter;
  using Superclass = ForwardFFTImageFilter<InputImageType, OutputImageType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  using InputPixelType = typename InputImageType::PixelType;
  using OutputPixelType = typename OutputImageType::PixelType;
  using ComplexType = OutputPixelType;
  using RealType = typename ComplexType::value_type;
  static_assert(std::is_same<RealType, float>::value || std::is_same<RealType, double>::value,
                "Unsupported pixel type");
  using SizeType = typename InputImageType::SizeType;
  using SizeValueType = typename InputImageType::SizeValueType;
  using OutputImageRegionType = typename OutputImageType::RegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(VkForwardFFTImageFilter, ForwardFFTImageFilter);

  static constexpr unsigned int ImageDimension = InputImageType::ImageDimension;

  itkGetMacro(DeviceID, uint64_t);
  itkSetMacro(DeviceID, uint64_t);

  SizeValueType
  GetSizeGreatestPrimeFactor() const override;

protected:
  VkForwardFFTImageFilter();
  ~VkForwardFFTImageFilter() override = default;

  void
  GenerateData() override;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  uint64_t m_DeviceID{ 0UL };
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkVkForwardFFTImageFilter.hxx"
#endif

#endif // itkVkForwardFFTImageFilter_h
