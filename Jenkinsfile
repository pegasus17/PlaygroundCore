pipeline{
  agent any
  stages{
    stage("Build"){
      steps{
          cmakeBuild(
            installation: "3.22.2",
            cleanBuild: true,
            buildDir: "build",
            generator: "Ninja",
            buildType: "Debug",
            steps: [
              [args: "all"],
              [args: "install"],
              [args: "package_source"]
            ]
          )
      }
      post {
        success {
          dir("install") {
            archiveArtifacts(
              followSymlinks: false,
              artifacts: "**/*"
            )
          }
        }
      }
    }
  }
}
