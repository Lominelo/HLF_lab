#!/bin/bash
# Package the application with required libraries
# Run after building with -DBUILD_APP=ON

BUILD_DIR="build"
DEPLOY_DIR="deploy"

mkdir -p "$DEPLOY_DIR"
cp "$BUILD_DIR/fourier_app" "$DEPLOY_DIR/"

# On macOS:
# macdeployqt "$DEPLOY_DIR/fourier_app"

# On Windows (run in Qt command prompt):
# windeployqt deploy/fourier_app.exe
# copy path\to\libfftw3-3.dll deploy\

echo "Application packaged in $DEPLOY_DIR/"
