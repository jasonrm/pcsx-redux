{ pkgs ? import <nixpkgs> {} }:
pkgs.callPackage ./derivation.nix {
  src = builtins.fetchGit {
    url = ./.;
    submodules = true;
  };
  stdenv = pkgs.llvmPackages_13.libcxxStdenv;
}
