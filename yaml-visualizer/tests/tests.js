import fs from "fs"
import { parse } from "yaml"

fs.readFile("kv.yaml", "utf-8", (err, data) => {
  console.log(parse(data))
})