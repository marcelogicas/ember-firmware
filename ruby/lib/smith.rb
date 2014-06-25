require 'bundler/setup'
require 'smith/version'

# Config options can be set through environment variables
# These are the defaults if not set
ENV['WPA_ROAM_PATH']      ||= '/etc/wpa_supplicant'
ENV['HOSTAPD_CONF_PATH']  ||= '/etc/hostapd'
ENV['DNSMASQ_CONF_PATH']  ||= '/etc'
ENV['STORAGE_PATH']       ||= '/var/local'
ENV['COMMAND_PIPE']       ||= '/tmp/command_pipe'
ENV['UPLOAD_PATH']        ||= '/var/local'
ENV['WIRELESS_INTERFACE'] ||= 'wlan1'
ENV['WIRED_INTERFACE']    ||= 'eth0'
ENV['AP_SSID']            ||= 'beaglebone'
ENV['AP_IP']              ||= '192.168.1.1/24'

module Smith
  module_function

  def root
    @root ||= File.expand_path('../..', __FILE__)
  end

  def command_pipe
    ENV['COMMAND_PIPE']
  end
end
