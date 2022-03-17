{ src ? ./.
, lib, stdenv, darwin
, pkg-config, imagemagick
, capstone, ffmpeg, freetype, glfw, libuv, zlib, curl
}:

stdenv.mkDerivation {
  name = "pcsx-redux";

  inherit src;

  preConfigure = ''
    export MAKEFLAGS=-j$NIX_BUILD_CORES
  '';
  makeFlags = [
    "DESTDIR=$(out)"
  ];

  nativeBuildInputs = [
    imagemagick
    pkg-config
  ];

  buildInputs = [
    capstone
    ffmpeg
    freetype
    glfw
    libuv
    zlib
    curl
  ] ++ lib.optionals stdenv.isDarwin (with darwin.apple_sdk.frameworks; [
    AudioToolbox
    Carbon
    Cocoa
    CoreAudio
    OpenGL
    GLUT
  ]);

  meta = with lib; {
    description = "Latest iteration on the PCSX emulator, heavily focused on development, debuggability, and reverse engineering";
    homepage = "https://pcsx-redux.consoledev.net/";
    license = licenses.gpl2;
  };
}
