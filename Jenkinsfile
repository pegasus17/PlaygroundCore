pipeline{
  agent any
  stages{
    stage("Build"){
      steps{
          cmakeBuild(
            installation: '3.22.2',
            cleanBuild: true,
            buildDir: 'build',
            generator: 'Ninja',
            buildType: 'Debug',
            steps: [[withCmake: true]]
          )
      }
    }
  }
}