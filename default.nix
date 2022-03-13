{ pkgs ? import <nixpkgs> {} }:
pkgs.callPackage ./derivation.nix {
    stdenv = pkgs.llvmPackages_13.libcxxStdenv;
}
