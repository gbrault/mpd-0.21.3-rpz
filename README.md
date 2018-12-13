# mpd-0.21.3-rpz
mpd 0.21.3 compiled for raspberry pi zero. Thereafter documention holds for comiling on a Raspberry Pi Zero (W), sure cross compiling on a more powerfull machine is the right option, but this works as well.

## Guidelines
Get the latest source (0.21.3 December 2018) and unzip it on local pi home directory
```
wget https://www.musicpd.org/download/mpd/0.21/mpd-0.21.3.tar.xz
tar xf mpd-0.21.3.tar.xz
cd mpd-0.21.3
```
Add all necessary dependencies
```
sudo apt-get install g++ \
  libpcre3-dev \
  libmad0-dev libmpg123-dev libid3tag0-dev \
  libflac-dev libvorbis-dev libopus-dev \
  libadplug-dev libaudiofile-dev libsndfile1-dev libfaad-dev \
  libfluidsynth-dev libgme-dev libmikmod2-dev libmodplug-dev \
  libmpcdec-dev libwavpack-dev libwildmidi-dev \
  libsidplay2-dev libsidutils-dev libresid-builder-dev \
  libavcodec-dev libavformat-dev \
  libmp3lame-dev libtwolame-dev libshine-dev \
  libsamplerate0-dev libsoxr-dev \
  libbz2-dev libcdio-paranoia-dev libiso9660-dev libmms-dev \
  libzzip-dev \
  libcurl4-gnutls-dev libyajl-dev libexpat-dev \
  libasound2-dev libao-dev libjack-jackd2-dev libopenal-dev \
  libpulse-dev libshout3-dev \
  libsndio-dev \
  libmpdclient-dev \
  libnfs-dev libsmbclient-dev \
  libupnp-dev \
  libavahi-client-dev \
  libsqlite3-dev \
  libsystemd-dev libwrap0-dev \
  libgtest-dev \
  libboost-dev \
  libicu-dev  
```
Install messon and ninja
```
sudo apt-get install python3 python3-pip ninja-build
sudo pip3 install meson
```
And now compile mpd
```
meson . output/release --buildtype=debugoptimized -Db_ndebug=true
meson configure output/release
ninja -C output/release
sudo ninja -C output/release install
```
 - mpd is in ./output/release
 - service files are ./output/release/systemd
 - use the mpdconf.example in ./doc for configuration

## other configuration optional settings

[optional: just if compile from source]

```
// swap increase for compile

sudo nano /etc/dphys-swapfile

# CONF_SWAPSIZE=100 to CONF_SWAPSIZE=1024

sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start

free -m to monitor status
# reset it back after compiling
```
Playing midi files
```
sudo apt-get install fluidsynth
```
