<template>
  <h1> Zumo GUI </h1>

  <IMUSensor></IMUSensor>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import IMUSensor from './components/IMUSensor.vue';

export default defineComponent({
  name: 'App',
  components: {
    IMUSensor
  }
});
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
