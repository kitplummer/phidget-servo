require 'rubygems'
require 'sinatra'

post '/api' do 
    puts "API -> Setting position: #{params[:position]}"
    r = `phidget-servo #{params[:position]}`   
    if r.include?("Success")
      "/api success"
    end 
end

get '/api' do
    "/api only accepts POSTs"
end

post '/' do
    r = `phidget-servo #{params[:position]}`   
    if r.include?("Success")
      @msg = "Moved to #{params[:position]} successfully."
      erb :index
    else
      "/api failure: #{r}"
    end
end

get '/' do
    erb :index
end