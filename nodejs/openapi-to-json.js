const fs = require('fs');
const yaml = require('js-yaml');

const SOURCE_PATH = './dist/openapi-dereferenced.yaml';
const DESTINATION_PATH = './dist/openapi-to-json.json';

const openapi = yaml.load(fs.readFileSync(SOURCE_PATH, 'utf8'));
const componentsSchema = openapi.components.schemas;

const convertOpenAPItoJSON = (openApi, input) => {
  for (const key in openApi) {
    if (openApi.hasOwnProperty(key)) {
      const openApiObject = openApi[key];
      if (openApiObject.type === 'object') {
        // If it's a "map"... Problem: how to generate avro-schema from an object that is supposed to be a map?
        if (openApiObject.additionalProperties) {
          if (openApiObject.example) {
            input[key] = openApiObject.example;
          } else {
            input[key] = { key: 'value' };
          }
        } else { // schema.properties
          input[key] = convertOpenAPItoJSON(openApiObject.properties, {});
        }
      } else if (openApiObject.type === 'array') {
        if (openApiObject.items.properties) {
          input[key] = [convertOpenAPItoJSON(openApiObject.items.properties, {})];
        } else if (openApiObject.example) {
          input[key] = openApiObject.example;
        } else if (openApiObject.items.type === 'string') {
          input[key] = ['value1', 'value2', 'value3'];
        } else {
          input[key] = [123, 456, 789];
        }
      } else if (openApiObject.type === 'string') {
        input[key] = (openApiObject.example && String(openApiObject.example)) || (openApiObject.example === null ? null : 'string');
      } else if (openApiObject.type === 'boolean') {
        input[key] = (openApiObject.example && Boolean(openApiObject.example)) || (openApiObject.example === null ? null : false);
      } else {
        // Problem: 123.0 === 123 for JavaScript, it can't serialize with zero unless changing type to string
        input[key] = (openApiObject.example && Number(openApiObject.example)) || (openApiObject.example === null ? null : 0);
      }
    }
  }

  return input;
};

const content = convertOpenAPItoJSON(componentsSchema, {});
fs.writeFileSync(DESTINATION_PATH, JSON.stringify(content, undefined, 2));
