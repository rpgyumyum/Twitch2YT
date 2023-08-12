

mnt51l94omwga9pdo9mskeaxd5fzsq
q9nhswkn2b8csepv5t5gmqtup3kz6h

#Auth token
curl -X POST 'https://id.twitch.tv/oauth2/token' \
-H 'Content-Type: application/x-www-form-urlencoded' \
-d 'client_id=mnt51l94omwga9pdo9mskeaxd5fzsq&client_secret=q9nhswkn2b8csepv5t5gmqtup3kz6h&grant_type=client_credentials' | jq '.access_token'


#Get a clip
curl -X GET 'https://api.twitch.tv/helix/clips?id=LovelyDrabBunnyPunchTrees-Q6V9M9b_jh0pVird' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq'


#GET TOP 5 clips
curl -X GET 'https://api.twitch.tv/helix/clips?game_id=516575&first=5&started_at=2023-07-22T15:00:14Z' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq' >> response.json


#GETGAMES
curl -X GET 'https://api.twitch.tv/helix/games?name=Valorant' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq' >> response.json

#get user id
curl -X GET 'https://api.twitch.tv/helix/users?login=papaplatte' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq' >> respnse.json


#get channel info 
curl -X GET 'https://api.twitch.tv/helix/channels?broadcaster_id=50985620' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq' >> respnse.json


    "broadcaster_id" : "568682215",
    "broadcaster_name" : "\u6a58\u3072\u306a\u306e",
    "created_at" : "2023-08-01T06:03:20Z",
    "creator_id" : "179104063",
    "creator_name" : "AndrewGarciaZ",
    "duration" : 17.800000000000001,
    "embed_url" : "https://clips.twitch.tv/embed?clip=RoughAthleticGarbageDancingBanana-iepeuadQlwbaSzzO",
    "game_id" : "516575",
    "id" : "RoughAthleticGarbageDancingBanana-iepeuadQlwbaSzzO",
    "language" : "ja",
    "thumbnail_url" : "https://clips-media-assets2.twitch.tv/AApByonqXrmnUJcG2ks8zg/AT-cm%7CAApByonqXrmnUJcG2ks8zg-preview-480x272.jpg",
    "title" : "\u4eca\u4e16\u7d00\u6700\u5927\u306e\u6cbc\u30a8\u30a4\u30e0\u306a\u306e",
    "url" : "https://clips.twitch.tv/RoughAthleticGarbageDancingBanana-iepeuadQlwbaSzzO",
    "video_id" : "1887104190",
    "view_count" : 4245,
    "vod_offset" : 4044


#list of top streams right now (streams == streamer) <-- ?
curl -X GET 'https://api.twitch.tv/helix/streams?first=20' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq'

#list of top games
curl -X GET 'https://api.twitch.tv/helix/games/top' \
-H 'Authorization: Bearer m4pd4g6klkwfk0nncdab6t6avoviuz' \
-H 'Client-Id: mnt51l94omwga9pdo9mskeaxd5fzsq' >> response.json
