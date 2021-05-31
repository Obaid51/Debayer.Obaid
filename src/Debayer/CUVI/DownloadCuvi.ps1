$org_url = "https://dev.azure.com/InFarm/"
$project_id = "9156b420-fe03-42c9-9d28-c26e83f94f4e"
$cuvi_version = "1.6.2"

az artifacts universal download --organization $org_url --project $project_id --scope project --feed "CUVI" --name "cuvi-linux" --version $cuvi_version --path .