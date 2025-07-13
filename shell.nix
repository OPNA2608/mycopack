let
  nixpkgs-src = builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/9807714d6944a957c2e036f84b0ff8caf9930bc0.tar.gz";
    sha256 = "sha256-LwWRsENAZJKUdD3SpLluwDmdXY9F45ZEgCb0X+xgOL0=";
  };
in

with import nixpkgs-src { };

let
  listToQtVar = suffix: lib.makeSearchPathOutput "bin" suffix;
in
mkShell {
  name = "mycemaze-shell";

  packages = with pkgs; [
    editorconfig-checker

    qt6.full

    cmake
    gdb
    qtcreator
  ];

  env = {
    QT_PLUGIN_PATH = listToQtVar qt6.qtbase.qtPluginPrefix (
      with qt6;
      [
        qtbase
        qtwayland
      ]
    );
    QML2_IMPORT_PATH = listToQtVar qt6.qtbase.qtQmlPrefix (
      with qt6;
      [
        qtdeclarative
      ]
    );
  };
}
