import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as wav


def fft(signal):
    if len(signal) < 2:
        return signal
    else:
        n = len(signal)
        even = fft(signal[0::2])
        odd = fft(signal[1::2])
        factor = np.exp(-1j * 2 * np.pi * np.arange(n)/n)
        return np.concatenate([even + factor[:n//2] * odd
                          ,
        even + factor[n//2:] * odd])
def ifft(signal):
    if len(signal) < 2:
        return signal
    else:
        n= len(signal)
    even = ifft(signal[0::2])
    odd = ifft(signal[1::2])
    factor = np.exp(1j * 2 * np.pi * np.arange(n)/n)
    return np.concatenate([even + factor[:n//2] * odd,
    even + factor[n//2:] * odd]) / 2
# Recipe (a): Transform the given voice signal to the Fourier domain using Fast Fourier Transform.
encoded_sample, encoded_data = wav.read("encoded.wav")
encoded_fft = fft(encoded_data)
freq_bins = np.arange(len(encoded_fft))
# Recipe (b): Split the Fourier domain representation into two parts, positive and negative frequencies,
middle = len(encoded_fft) // 2
positive_freq = encoded_fft[:middle]
negative_freq = encoded_fft[middle:]
reversed_encoded_fft = np.concatenate([positive_freq[::-1], negative_freq[::-1]])
# Recipe (c): Return to the time domain using Inverse Fast Fourier Transform and listen the message.
decoded_signal = ifft(reversed_encoded_fft)
decoded_data = decoded_signal.real.astype(np.int16)
decoded_fft = fft(decoded_data)
wav.write("reconstructed.wav", encoded_sample, decoded_data)
wav.write("rd.wav", encoded_sample, decoded_data)

plt.figure(figsize=(10, 4))
plt.title("Encoded Signal Time Domain")
plt.xlabel("Signal")
plt.ylabel("Amplitude")
plt.plot(encoded_data)
plt.savefig("encoded_time_domain.png")
plt.show()
# Time domain plot - decoded signal
plt.figure(figsize=(10, 4))
plt.title("Time Domain - Decoded Signal")
plt.xlabel("Signal")
plt.ylabel("Amplitude")
plt.plot(decoded_data)
plt.savefig("decoded_time_domain.png")
plt.close()
# Frequency magnitude plot - encoded signal
plt.figure(figsize=(10, 4))
plt.title("Encoded Signal Frequency Magnitude ")
plt.xlabel("Frequency Bin")
plt.ylabel("Magnitude")
plt.plot(freq_bins, np.abs(encoded_fft))
plt.savefig("encoded_frequency_magnitude.png")
plt.close()
# Frequency magnitude plot - decoded signal
plt.figure(figsize=(10, 4))
plt.title("Decoded Signal Frequency Magnitude")
plt.xlabel("Frequency Bin")
plt.ylabel("Magnitude")
plt.plot(freq_bins, np.abs(decoded_fft))
plt.savefig("decoded_frequency_domain.png")
plt.show()