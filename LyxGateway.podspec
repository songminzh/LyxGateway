Pod::Spec.new do |s|
  s.name             = "LyxGateway"
  s.version          = "1.0.0"
  s.summary          = "Laiyouxi gateway platform SDK for iOS"
  s.description      = <<-DESC
                       It is a Laiyouxi gateway platform SDK for iOS, which implement by Objective-C.
                       DESC
  s.homepage         = "https://github.com/songminzh/LyxGateway"
  s.license          = 'MIT'
  s.author           = { "zheng" => "murphyzh06@gmail.com" }
  s.source           = { :git => "https://github.com/songminzh/LyxGateway.git", :tag => s.version }
  # s.social_media_url = 'https://twitter.com/NAME'
  # s.screenshots      = "www.example.com/screenshots_1", "www.example.com/screenshots_2"

  s.platform     = :ios
  s.ios.deployment_target = '10.0'
  # s.osx.deployment_target = '10.7'
  s.requires_arc = true

  # s.ios.exclude_files = 'Classes/osx'
  # s.osx.exclude_files = 'Classes/ios'
  # s.public_header_files = 'Classes/**/*.h'
  s.vendored_frameworks = 'LyxGateway.framework'
  s.resources = 'LyxGateway.bundle'
  s.frameworks = 'Foundation'

end