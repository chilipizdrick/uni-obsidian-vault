{
  description = "Ultimate c++ development flake for uni";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
        llvm = pkgs.llvmPackages_latest;
        lib = nixpkgs.lib;
      in {
        devShell = pkgs.mkShell {
          nativeBuildInputs = [
            llvm.clang
          ];

          buildInputs = [
            llvm.libcxx
          ];

          packages = [
            pkgs.lldb
          ];

          CLANGD_FLAGS = "--query-driver=${pkgs.clang}/bin/clang";
          CPATH = builtins.concatStringsSep ":" [
            (lib.makeSearchPathOutput "dev" "include" [llvm.libcxx])
            (lib.makeSearchPath "resource-root/include" [llvm.clang])
          ];
        };
      }
    );
}
